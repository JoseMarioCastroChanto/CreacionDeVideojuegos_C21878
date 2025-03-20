#include "game/Game.h"
#include <iostream>

int main(int argc, char* argv[]){
    std::cout<<"Intro a motor SDL2" << std::endl;
    Game game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}