#include "Game.h"
#include <iostream>

Game:: Game(){
 std::cout << "Se ejecuta constructor Game"<< std::endl; 
 }

Game:: ~Game(){
 std::cout << "Se ejecuta destructor Game"<< std::endl; 
 }

 void Game::init(){
    // Inicializar SDL2
     if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error al inicializar SDL" << std::endl;
        return;
    }

    this->windowWidth= 800;
     this->windowHeight = 600;

      //Creacion de la ventana
    this->window = SDL_CreateWindow(
        "MiniMotor", //Titulo de la ventana
        SDL_WINDOWPOS_CENTERED, //Pos x en la pantalla
        SDL_WINDOWPOS_CENTERED, //Pos y en la pantalla
        this->windowWidth, //Ancho
        this->windowHeight, //Alto
        SDL_WINDOW_SHOWN //Flags

    );

    // Crear renderer
    renderer = SDL_CreateRenderer(
      this->window,
      -1, //Driver de la pantalla
      0 // Flags  
    );

    this->isRunning = true;


 }

void Game::processInput(){
     //Registro que almacena los datos de evento
        SDL_Event sdlEvent;

        // SDL_PollEvent saca de la cola de eventos de SDL un evento pendiente y lo
        // almacena en un registro de tipo SDL_Event
        while(SDL_PollEvent(&sdlEvent)){
            switch(sdlEvent.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                break;
            default:
                break;
            }

        }

        //Limpiar ventana
        SDL_RenderClear(renderer);
        //Actualizar ventana
        SDL_RenderPresent(renderer);

}

void::Game::render(){
    //Establece el color con el que se va a dibujar la ventana
    SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
    //Limpiar ventana
    SDL_RenderClear(this->renderer);
    //Actualizar ventana
    SDL_RenderPresent(this->renderer);

}

void Game::run(){
    while(this->isRunning){
        processInput();
        //update();
        render();
        }
 }

void Game::destroy(){
    // Liberar recursos
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
 }

