#ifndef DEFEATYSTEM_HPP
#define DEFEATYSTEM_HPP

#include "../Components/LifeComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class DefeatSystem
 * @brief Checks if any objective entity is defeated (life <= 0).
 * 
 * If any objective entity without the TagProjectileComponent reaches zero or less life,
 * the Defeat flag is set to true.
 */
class DefeatSystem : public System{
    public:
     /**
     * @brief Constructs the DefeatSystem requiring LifeComponent and TagObjectiveComponent.
     */
     bool Defeat = false;
     DefeatSystem(){
        RequireComponent<LifeComponent>();
        RequireComponent<TagObjectiveComponent>();

     }
    /**
     * @brief Updates the system, checking all objective entities for defeat.
     * 
     * Sets Defeat to true if any objective entity without TagProjectileComponent
     * has life_count <= 0.
     */
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