#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"


/**
 * @class RenderTextSystem
 * @brief System responsible for rendering text components in the ECS.
 * 
 * Requires entities to have TextComponent and TransformComponent.
 */
class RenderTextSystem : public System {
 public:
     /**
     * @brief Constructs a RenderTextSystem and requires TextComponent and TransformComponent.
     */
    RenderTextSystem(){
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }
    /**
     * @brief Updates and renders all text entities.
     * 
     * For each entity:
     * - Renders the text surface with the font and color specified in TextComponent.
     * - Creates a texture from the surface.
     * - Uses the TransformComponent for positioning and scaling.
     * - Renders the texture on the screen.
     * - Frees the texture and surface after rendering.
     * 
     * @param renderer Pointer to the SDL_Renderer used for rendering.
     * @param assetManager Shared pointer to AssetManager to access fonts.
     */
    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>&
    assetManager){
        for(auto entity : GetSystemEntities()){
            auto& text = entity.GetComponent<TextComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();

            SDL_Surface* surface = TTF_RenderText_Blended(
                assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
            text.width = surface->w;
            text.height = surface->h;
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_Rect dstRect = {
              static_cast<int>(transform.position.x),
              static_cast<int>(transform.position.y),
              text.width * static_cast<int>(transform.scale.x),
              text.height * static_cast<int>(transform.scale.y)
            };

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
    /**
     * @brief Renders fixed text at specified screen coordinates with optional scaling.
     * 
     * This function does not depend on ECS entities.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     * @param font Pointer to the TTF_Font to use.
     * @param text The text string to render.
     * @param color The SDL_Color to render the text with.
     * @param x The x position on screen.
     * @param y The y position on screen.
     * @param scaleX Optional horizontal scale factor (default 1.0).
     * @param scaleY Optional vertical scale factor (default 1.0).
     */
void RenderFixedText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f) {
 
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) {
        SDL_Log("Error creando surface para texto fijo: %s", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        SDL_Log("Error creando textura para texto fijo: %s", SDL_GetError());
        return;
    }

    SDL_Rect dstRect = {
        x,
        y,
        static_cast<int>(surface->w * scaleX),
        static_cast<int>(surface->h * scaleY)
    };

    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}
};

#endif