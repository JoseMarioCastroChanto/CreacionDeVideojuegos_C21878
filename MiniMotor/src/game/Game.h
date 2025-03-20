#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <SDL2/SDL_mixer.h>  
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <string>

class Game{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;

    TTF_Font* font = nullptr;
    int fontSize = 0;
    SDL_Color fontColor = {0,0,0};

    bool isRunning = false;

    //Atributos ncesarios de la imagen
    SDL_Texture* imgTexture = nullptr;
    glm::vec2 pos = glm::vec2();
    size_t imageWidth = 0;
    size_t imageHeight=0;
    SDL_Rect srcRect = {0,0,0,0};
    double angle = 0.0;

    //Atributos del texto
    SDL_Texture* txtTexture = nullptr;
    std::string message = "";
    glm::vec2 txtPos = glm::vec2();
    size_t txtWidth = 0;
    size_t txtHeight=0;
    double txtAngle = 0.0;

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