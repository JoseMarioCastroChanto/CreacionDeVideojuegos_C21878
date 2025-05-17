#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderSystem : public System {
  public:
   RenderSystem(){
    RequireComponent<SpriteComponent>();
    RequireComponent<TransformComponent>();
   }

 void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& AssetManager) {
    std::vector<Entity> sortedEntities;

    for (auto entity : GetSystemEntities()) {
        sortedEntities.push_back(entity);
    }

   std::sort(sortedEntities.begin(), sortedEntities.end(), [](const Entity& a, const Entity& b) {
    bool aHasDepth = a.HasComponent<DepthComponent>();
    bool bHasDepth = b.HasComponent<DepthComponent>();

    if (aHasDepth != bHasDepth) {
        return !aHasDepth; 
    }

    if (!aHasDepth && !bHasDepth) {
        return a.GetId() < b.GetId(); 
    }
    // Regla de 3 para escalas comparables
    auto aDepth = a.GetComponent<DepthComponent>();
    auto aTransform = a.GetComponent<TransformComponent>();
    aTransform.scale.y = aTransform.scale.y*10/aDepth.max_scale;
    
    auto bTransform = b.GetComponent<TransformComponent>();
    auto bDepth = b.GetComponent<DepthComponent>();
    bTransform.scale.y = bTransform.scale.y*10/bDepth.max_scale;
    
    return aTransform.scale.y < bTransform.scale.y;
});

    for (auto entity : sortedEntities) {
        const auto sprite = entity.GetComponent<SpriteComponent>();
        const auto transform = entity.GetComponent<TransformComponent>();

        SDL_Rect srcRect = sprite.srcRect;
        SDL_Rect dstRect = {
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            static_cast<int>(sprite.width * transform.scale.x),
            static_cast<int>(sprite.height * transform.scale.y),
        };

        SDL_RenderCopyEx(
            renderer,
            AssetManager->GetTexture(sprite.textureId),
            &srcRect,
            &dstRect,
            transform.rotation,
            nullptr,
            SDL_FLIP_NONE
        );
    }
 }

};




#endif