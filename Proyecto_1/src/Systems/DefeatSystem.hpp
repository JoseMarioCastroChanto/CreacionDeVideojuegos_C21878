#ifndef DEFEATYSTEM_HPP
#define DEFEATYSTEM_HPP

#include "../Components/LifeComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../ECS/ECS.hpp"

class DefeatSystem : public System{
    public:
     bool Defeat = false;
     DefeatSystem(){
        RequireComponent<LifeComponent>();
        RequireComponent<TagObjectiveComponent>();

     }

    void Update() {
        for(auto entity : GetSystemEntities()){
            const auto& life = entity.GetComponent<LifeComponent>();
            if(life.life_count <= 0){
                if(!entity.HasComponent<TagProjectileComponent>()){
                    Defeat = true;
                    break;
                }
            }

        }
    }
};

#endif