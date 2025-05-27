#ifndef HEALTHBARSYSTEM_HPP
#define HEALTHBARSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include <SDL2/SDL.h>
#include "../Components/LifeComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"

/**
 * @class HealthBarSystem
 * @brief System responsible for rendering health bars for entities with LifeComponent and TagObjectiveComponent.
 * 
 * This system draws the health bars differently depending on whether the entity has a TagPlayerComponent or not.
 * For player entities, the health bar is drawn at position (100, 50) with a green fill.
 * For other objective entities (e.g., obelisks), the health bar is drawn at position (100, 80) with a blue fill.
 */
class HealthBarSystem : public System {
public:
    /**
     * @brief Constructs a HealthBarSystem and requires LifeComponent and TagObjectiveComponent.
     */
    HealthBarSystem() {
        RequireComponent<LifeComponent>();
         RequireComponent<TagObjectiveComponent>();
        
    }

    /**
     * @brief Updates and renders health bars for all entities in the system.
     * 
     * @param renderer Pointer to the SDL_Renderer used for drawing the health bars.
     * 
     * For each entity:
     * - Retrieves the LifeComponent to get current and maximum life.
     * - Draws a white border rectangle.
     * - Fills the rectangle proportionally to the entity's current life.
     * - Uses green color for player entities and blue for others.
     */
    void Update(SDL_Renderer* renderer) {
        for (auto entity : GetSystemEntities()) {
            const auto& life = entity.GetComponent<LifeComponent>();

            SDL_Rect borderRect;
            SDL_Rect fillRect;

            if (entity.HasComponent<TagPlayerComponent>()) {
                // Jugador
                borderRect = { 100, 50, 300, 20 };
                fillRect = { 100, 50, static_cast<int>(300 * (static_cast<float>(life.life_count) / life.life_max)), 20 };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &borderRect);

                SDL_SetRenderDrawColor(renderer, 0, 160, 0, 255);
                SDL_RenderFillRect(renderer, &fillRect);
            } 
            else {
                // Obelisko
                borderRect = { 100, 80, 300, 20 };
                fillRect = { 100, 80, static_cast<int>(300 * (static_cast<float>(life.life_count) / life.life_max)), 20 };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &borderRect);

                SDL_SetRenderDrawColor(renderer, 0, 90, 180, 255);  
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }
};

#endif