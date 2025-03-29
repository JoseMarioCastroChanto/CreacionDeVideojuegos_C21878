#include "Game.hpp"

#include <iostream>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"

Game::Game(){
    std::cout<< "[Game] Se ejecuta constructor" << std::endl;
    assetManager = std::make_unique<AssetManager>();
    registry = std::make_unique<Registry>();
}

Game::~Game(){
    assetManager.reset();
    registry.reset();

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

    windowWidth = 800;
    windowHeight = 600;

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
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();

    assetManager->AddTexture(renderer, "enemy_alan", "./assets/images/enemy_alan.png");
    Entity enemy = registry->CreateEntity();

    enemy.AddComponent<RigidBodyComponent>(glm::vec2(50,0));
    enemy.AddComponent<SpriteComponent>("enemy_alan", 16, 16, 0, 0);
    enemy.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0)
      , glm::vec2(2.0, 2.0), 0.0);

}

void Game::ProcessInput(){
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)){
        switch(sdlEvent.type){
            case SDL_QUIT:
              isRunning = false;
              break;
            case SDL_KEYDOWN:
              if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
              }
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
    registry->Update();

    registry->GetSystem<MovementSystem>().Update(deltaTime);
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetManager);

    SDL_RenderPresent(renderer);
}

void Game::Run(){
    Setup();
    while (isRunning){
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}




