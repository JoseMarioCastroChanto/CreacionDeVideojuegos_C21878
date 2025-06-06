#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/TagWallComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagEnemyComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"
#include "../Components/LifeComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../Systems/EntitySpawnerSystem.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class DamageSystem
 * @brief Handles damage application between entities when collisions occur.
 * 
 * This system listens for collision events and processes damage interactions 
 * between entities based on their components and tags (e.g., enemy, projectile, objective).
 * It also manages entity destruction and explosion creation when life reaches zero.
 */
class DamageSystem : public System {
 public:
  /**
   * @brief Constructs the DamageSystem and requires entities to have CircleColliderComponent.
   */
  DamageSystem(){
    RequireComponent<CircleColliderComponent>();
  }
  /**
   * @brief Subscribes the DamageSystem to CollisionEvent notifications from the EventManager.
   * @param eventManager A unique pointer to the EventManager instance.
   */
  void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager){
    eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
    &DamageSystem::OnCollision);
  }
  /**
   * @brief Called when a CollisionEvent is emitted.
   * Processes damage between entities involved in the collision.
   * 
   * @param e Reference to the CollisionEvent containing the colliding entities.
   */
void OnCollision(CollisionEvent& e){
    std::cout<< "[DamageSystem] Colisión de la entidad " << e.a.GetId()
    << " y " << e.b.GetId() << std::endl;

    if(e.a.HasComponent<LifeComponent>() && e.b.HasComponent<LifeComponent>()){
      auto& alife = e.a.GetComponent<LifeComponent>().life_count;
      auto& blife = e.b.GetComponent<LifeComponent>().life_count;
      auto& aScale = e.a.GetComponent<TransformComponent>().scale.x;
      auto& bScale = e.b.GetComponent<TransformComponent>().scale.x;
      auto& aMaxScale = e.a.GetComponent<DepthComponent>().max_scale;
      auto& bMaxScale = e.b.GetComponent<DepthComponent>().max_scale;

      if((e.a.HasComponent<TagEnemyComponent>() && !e.b.HasComponent<TagEnemyComponent>() &&
      e.b.HasComponent<TagProjectileComponent>() ) 
      || (e.b.HasComponent<TagEnemyComponent>() && !e.a.HasComponent<TagEnemyComponent>()
      && e.a.HasComponent<TagProjectileComponent>()) ){
          alife -= e.b.GetComponent<DamageComponent>().damage_dealt;
          blife -= e.a.GetComponent<DamageComponent>().damage_dealt;
      }

      if(e.a.HasComponent<TagEnemyComponent>() && e.b.HasComponent<TagObjectiveComponent>()
      && !e.b.HasComponent<TagProjectileComponent>()){
          blife -= e.a.GetComponent<DamageComponent>().damage_dealt;
          if(e.a.HasComponent<TagEnemyComponent>()&& e.a.HasComponent<TagProjectileComponent>()){
              alife -= 1;
          }
      }
      if(e.b.HasComponent<TagEnemyComponent>() && e.a.HasComponent<TagObjectiveComponent>()
      && !e.a.HasComponent<TagProjectileComponent>()){
          alife -= e.b.GetComponent<DamageComponent>().damage_dealt;
          if(e.b.HasComponent<TagEnemyComponent>()&& e.b.HasComponent<TagProjectileComponent>()){
              blife -= 1;
          }
      }
    bool oneExplosion = true;
      if(alife <= 0){
          double scale = (aScale*6)/aMaxScale;
          CreateExplosion(e.a,10,scale);
          e.a.Kill();
          oneExplosion = false;
      }
      if(blife <= 0){
        if(oneExplosion){
           double scale = (bScale*6)/bMaxScale;
           CreateExplosion(e.b,10,scale); 
        }
          e.b.Kill();
      }  



    }

}

  /**
   * @brief Destroys all entities tagged as enemies (excluding players), triggering explosions.
   */
void DestroyAllEnemies (){
       for(auto entity : GetSystemEntities()){
            if(entity.HasComponent<TagEnemyComponent>() && !entity.HasComponent<TagPlayerComponent>()){
                auto& Scale = entity.GetComponent<TransformComponent>().scale.x;
                auto& MaxScale = entity.GetComponent<DepthComponent>().max_scale;
                double scale = (Scale*6)/MaxScale;
                CreateExplosion(entity,10,scale); 
                entity.Kill();
            }
        }
}
  /**
   * @brief Creates an explosion entity at the position of the given entity.
   * 
   * @param entity The entity at whose position the explosion is spawned.
   * @param num The number of entities or particles to spawn for the explosion.
   * @param scale The scale factor for the explosion visual size.
   */
void CreateExplosion(Entity entity, int num, double scale){
    auto& transform = entity.GetComponent<TransformComponent>();
    Entity newEntity = Game::GetInstance().registry->GetSystem<EntitySpawnerSystem>().GenerateEntity(
        Game::GetInstance().registry,num,Game::GetInstance().lua
    );
        auto& transformNew = newEntity.GetComponent<TransformComponent>();
        transformNew.position = transform.position;
        transformNew.scale.x = scale;
        transformNew.scale.y = scale;
}
};
#endif