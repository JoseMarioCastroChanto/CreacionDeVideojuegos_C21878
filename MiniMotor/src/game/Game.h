#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <SDL2/SDL_mixer.h>  
#include <glm/glm.hpp>
#include <sol/sol.hpp>

class Game{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;
    bool isRunning = false;

    //Atributos ncesarios de la imagen
    SDL_Texture* imgTexture = nullptr;
    glm::vec2 pos = glm::vec2();
    size_t imageWidth = 0;
    size_t imageHeight=0;
    SDL_Rect srcRect = {0,0,0,0};
    double angle = 0.0;

    void processInput();
    void update();
    void render();

public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
};
#endif