#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> 
#include <glm/glm.hpp>
#include <sol/sol.hpp>

class Game{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    size_t windowWidth = 0;
    size_t windowHeight = 0;
    bool isRunning = false;

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