#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

struct AnimationComponent {
 int numFrames;
 int currentFrame;
 int frameSpeedRate;
 bool isLoop;
 int startTime;

 AnimationComponent(int numFrames = 1, int frameSpeedRate = 1
 , bool isLoop = true){
    this->numFrames = numFrames;
    this->currentFrame = 1;
    this->frameSpeedRate = frameSpeedRate;
    this->isLoop = isLoop;
    this->startTime = SDL_GetTicks();
 }
};
#endif