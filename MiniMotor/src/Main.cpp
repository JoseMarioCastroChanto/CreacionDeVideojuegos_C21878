#include "game/Game.h"
#include <iostream>

int main(int argc, char* argv[]){
    Game game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}