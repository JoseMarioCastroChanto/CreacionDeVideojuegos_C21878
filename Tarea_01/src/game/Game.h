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
    SDL_Color fontColor = {0,0,0};
    int size = 0;
};

class Game{
    SDL_Window* window = nullptr;
    Window windowData;
    SDL_Renderer* renderer = nullptr;

    TTF_Font* font = nullptr;
    Font fontData;

    Entity<Calavera> calavera;
    Entity<Anillo> anillo;
    Entity<Carta> carta;

    bool isRunning = false;
    int mPrvsFrame = 0;

    void getConfig();
    template<typename T>
    void loadEntity(Entity<T>& , std::ifstream&,std::string);
    template<typename T>
    void initEntity(Entity<T>&);
    void processInput();
    void update();
    template<typename T>
    void updateEntity(Entity<T>&,double);
    void render();
    template<typename T>
    void renderEntity(Entity<T>&);
    template<typename T>
    void destroyEntity(Entity<T>&);

public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
};
#endif