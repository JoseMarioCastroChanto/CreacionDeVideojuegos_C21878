#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <SDL2/SDL_mixer.h>  
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <string>
#include <vector>
#include "Entity.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000/FPS; //16.6

struct Window{
    int windowWidth = 0;
    int windowHeight = 0;
    int r = 0, g = 0, b = 0;
};

struct Font{
    std::string directory;
    SDL_Color fontColor =  {0,0,0};
    int size = 0;
};

class Game{
    SDL_Window* window = nullptr;
    Window windowData;
    SDL_Renderer* renderer = nullptr;

    TTF_Font* font = nullptr;
    Font fontData;

    std::vector<std::unique_ptr<Entity>> entities;

    bool isRunning = false;
    bool isPaused = false;
    bool wasPaused = false;
    int mPrvsFrame = 0;

    void getConfig();
    void loadFont(std::ifstream&);
    void loadWindow(std::ifstream&);
    void loadEntity(std::unique_ptr<Entity>& , std::ifstream&);
    void initEntity(std::unique_ptr<Entity>&);
    void processInput();
    void update();
    void updateEntity(std::unique_ptr<Entity>&,double);
    void render();
    void renderEntity(std::unique_ptr<Entity>&);
    void destroyEntity(std::unique_ptr<Entity>&);

public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
};
#endif