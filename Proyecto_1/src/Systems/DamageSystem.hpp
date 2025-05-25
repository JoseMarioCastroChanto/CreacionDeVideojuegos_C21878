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
#include "../Components/EntitySpawnerComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
 public:
  DamageSystem(){
    RequireComponent<CircleColliderComponent>();
  }

  void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager){
    eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
    &DamageSystem::OnCollision);
  }

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

void CreateExplosion(Entity entity, int num, double scale){

}
};
#endif