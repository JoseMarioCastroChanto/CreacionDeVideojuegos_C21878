#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/TagWallComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagEnemyComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../Components/LifeComponent.hpp"
#include "../Components/DamageComponent.hpp"
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

      if(alife <= 0){
          e.a.Kill();
      }
      if(blife <= 0){
          e.b.Kill();
      }  



    }

}

void DestroyAllEnemies (){
       for(auto entity : GetSystemEntities()){
            if(entity.HasComponent<TagEnemyComponent>()){
                entity.Kill();
            }
        }
}
};
#endif