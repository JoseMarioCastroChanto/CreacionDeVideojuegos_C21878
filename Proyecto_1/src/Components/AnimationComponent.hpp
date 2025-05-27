#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @file AnimationComponent.hpp
 * @brief Defines the AnimationComponent used for animated entities.
 */

/**
 * @struct AnimationComponent
 * @brief Holds data for sprite-based animations, including frame count, speed, looping, and timing.
 */
struct AnimationComponent {
    int numFrames;        /**< Total number of frames in the animation. */
    int currentFrame;     /**< The current frame being displayed. */
    int frameSpeedRate;   /**< The speed rate of the animation (in ms per frame). */
    bool isLoop;          /**< Whether the animation should loop when it ends. */
    int startTime;        /**< The time when the animation started (in ms since SDL initialization). */

    /**
     * @brief Constructs a new AnimationComponent.
     * @param numFrames Number of frames in the animation. Default is 1.
     * @param frameSpeedRate Time per frame in milliseconds. Default is 1.
     * @param isLoop Whether the animation loops. Default is true.
     */
    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true){
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif
