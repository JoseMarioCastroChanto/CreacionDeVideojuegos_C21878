#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

/**
 * @file SpriteComponent.hpp
 * @brief Component for rendering a sprite with a texture and source rectangle.
 */

/**
 * @struct SpriteComponent
 * @brief Holds data for rendering a sprite, including texture ID and source rectangle.
 */
struct SpriteComponent {
    std::string textureId; /**< Identifier for the texture resource */
    int width;             /**< Width of the sprite */
    int height;            /**< Height of the sprite */
    SDL_Rect srcRect;      /**< Source rectangle from the texture to render */

    /**
     * @brief Construct a new SpriteComponent object
     * 
     * @param textureId Identifier of the texture to use (default "none")
     * @param width Width of the sprite (default 0)
     * @param height Height of the sprite (default 0)
     * @param srcRectX X coordinate of the source rectangle in the texture (default 0)
     * @param srcRectY Y coordinate of the source rectangle in the texture (default 0)
     */
    SpriteComponent(const std::string& textureId = "none", int width = 0,
                    int height = 0, int srcRectX = 0, int srcRectY = 0){
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif
