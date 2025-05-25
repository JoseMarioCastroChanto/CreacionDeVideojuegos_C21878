#ifndef HEALTHBARSYSTEM_HPP
#define HEALTHBARSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include <SDL2/SDL.h>
#include "../Components/LifeComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"

class HealthBarSystem : public System {
public:
    HealthBarSystem() {
        RequireComponent<LifeComponent>();
         RequireComponent<TagObjectiveComponent>();
        
    }

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