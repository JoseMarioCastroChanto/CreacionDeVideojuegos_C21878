#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class AnimationSystem
 * @brief System responsible for updating the animation frames of entities.
 *
 * This system requires entities to have both AnimationComponent and SpriteComponent.
 * It updates the current animation frame based on time and adjusts the source
 * rectangle of the sprite accordingly.
 */
class AnimationSystem : public System{
  public:
  /**
    * @brief Constructs the AnimationSystem and sets required components.
    */
   AnimationSystem() {
    RequireComponent<AnimationComponent>();
    RequireComponent<SpriteComponent>();
   }

   /**
    * @brief Updates all entities in the system by advancing their animation frames.
    *
    * Calculates the current animation frame based on the elapsed time,
    * the animation frame speed rate, and the total number of frames.
    * Updates the sprite's source rectangle x position to reflect the current frame.
    */
   void Update(){
    for(auto entity : GetSystemEntities()){
        auto& animation = entity.GetComponent<AnimationComponent>();
        auto& sprite = entity.GetComponent<SpriteComponent>();

        animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate/1000)
        % animation.numFrames;

        sprite.srcRect.x = animation.currentFrame * sprite.width;
    }
   }
};
#endif