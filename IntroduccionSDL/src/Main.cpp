// Documentacion en https://wiki.libsdl.org/SDL2
#include <SDL2/SDL.h> 
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <iostream>

int main(int argc, char* argv[]){
    std::cout<<"Intro a SDL2" << std::endl;

    glm::vec2 pos = glm::vec2(65.0f, 98.0f);

    sol::state lua;
    

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int width = 800;
    int height = 600;

    bool isRunning = true;

    // rectangulo de SDL2
    SDL_Rect rect = {
        (width / 2) -25, //Posicion x
        (height / 2) -25, //Posicion y
        50, //Ancho
        50 //Alto
    };

    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error al inicializar SDL" << std::endl;
    }

    //Creacion de la ventana
    window = SDL_CreateWindow(
        "Intro a SDL", //Titulo de la ventana
        SDL_WINDOWPOS_CENTERED, //Pos x en la pantalla
        SDL_WINDOWPOS_CENTERED, //Pos y en la pantalla
        width, //Ancho
        height, //Alto
        SDL_WINDOW_SHOWN //Flags

    );

    renderer = SDL_CreateRenderer(
      window,
      -1, //Driver de la pantalla
      0 // Flags  
    );

    while(isRunning){
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
        //Establece el color cpn el que se va a dibujar la ventana
        SDL_SetRenderDrawColor(renderer, 255, 255, 24, 255);

        //Limpiar ventana
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 167, 50, 245, 255);
        //Dibuja un rectangulo en la ventana
        SDL_RenderFillRect(renderer, &rect);

        //Actualizar ventana
        SDL_RenderPresent(renderer);
    }
    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}