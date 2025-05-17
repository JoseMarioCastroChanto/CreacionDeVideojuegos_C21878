#include "Game.hpp"

#include <iostream>

#include "../Events/ClickEvent.hpp"

#include "../Systems/CollisionSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/WallCollisionSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/DepthSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/SceneTimeSystem.hpp"
#include "../Systems/EntitySpawnerSystem.hpp"
#include "../Systems/CleanSystem.hpp"

Game::Game(){
    std::cout<< "[Game] Se ejecuta constructor" << std::endl;
    assetManager = std::make_unique<AssetManager>();
    controllerManager = std::make_unique<ControllerManager>();
    eventManager = std::make_unique<EventManager>();
    registry = std::make_unique<Registry>();
    sceneManager = std::make_unique<SceneManager>();
}

Game::~Game(){
    assetManager.reset();
    controllerManager.reset();
    eventManager.reset();
    registry.reset();
    sceneManager.reset();

    std::cout<< "[Game] Se ejecuta destructor" << std::endl;
}

Game& Game::GetInstance(){
    static Game game;
    return game;
}

void Game::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "[GAME] Error al inciializar SDL" << std::endl;
        return;
    }
    if(TTF_Init() != 0){
        std::cout << "[GAME] Error al inciializar SDL_ttf" << std::endl;
        return;
    }

    windowWidth = 1600;
    windowHeight = 900;

    window = SDL_CreateWindow(
        "Motor de juegos 2D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        std::cout << "[GAME] Error al crear ventana" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        std::cout << "[GAME] Error al crear renderer" << std::endl;
        return;
    }

    isRunning = true;
}

void Game:: Setup(){
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<WallCollisionSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<EntitySpawnerSystem>("./assets/scripts/dynamic_entities.lua",
    lua);
    registry->AddSystem<DepthSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<ScriptSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<UISystem>();
    registry->AddSystem<SceneTimeSystem>();
    registry->AddSystem<CleanSystem>();

    sceneManager->LoadSceneFromScript("./assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math);
    registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);

}

void Game::ProcessInput(){
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)){
        switch(sdlEvent.type){
            case SDL_QUIT:
              sceneManager->StopScene();
              isRunning = false;
              break;
            case SDL_KEYDOWN:
              if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                sceneManager->StopScene();
                isRunning = false;
                break;
              }
              controllerManager-> KeyDown(sdlEvent.key.keysym.sym);
              break;
            case SDL_KEYUP:
              controllerManager-> KeyUp(sdlEvent.key.keysym.sym);
              break;
            case SDL_MOUSEMOTION:
                int x, y;
                SDL_GetMouseState(&x, &y);
                controllerManager->SetMousePosition(x,y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                controllerManager->SetMousePosition(sdlEvent.button.x
                , sdlEvent.button.y);
                controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
                eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button)
                , sdlEvent.button.x , sdlEvent.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                controllerManager->SetMousePosition(sdlEvent.button.x
                , sdlEvent.button.y);
                controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
                break;
            default:
                break;

        }
    }

}

void Game::Update(){
    int timeToWait = MILISECS_PER_FRAME - (SDL_GetTicks() - milisecsPreviousFrame);
    if(0 < timeToWait && timeToWait <= MILISECS_PER_FRAME){
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks()- milisecsPreviousFrame) / 1000.0;
    // TODO: agregar esta variable al estado de LUA

    milisecsPreviousFrame = SDL_GetTicks();

    // Reiniciar las subscripciones
    eventManager->Reset();
    registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
    registry->GetSystem<WallCollisionSystem>().SubscribeToCollisionEvent(eventManager);
    registry->GetSystem<UISystem>().SubscribeToClickEvent(eventManager);
    
    registry->Update();

    registry->GetSystem<SceneTimeSystem>().Update();
    registry->GetSystem<ScriptSystem>().Update(lua);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<DepthSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update(eventManager);
    registry->GetSystem<CleanSystem>().Update();
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetManager);
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetManager);

    SDL_RenderPresent(renderer);
}

void Game::RunScene(){
    sceneManager->LoadScene();

    while(sceneManager->IsSceneRunning()){
        ProcessInput();
        Update();
        Render();
    }

    assetManager->ClearAssets();
    registry->ClearAllEntities();
}

void Game::Run(){
    Setup();
    while (isRunning){
        sceneManager->StartScene();
        RunScene();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}




