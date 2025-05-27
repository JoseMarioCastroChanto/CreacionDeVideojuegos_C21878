#ifndef CLEANSYSTEM_HPP
#define CLEANTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class CleanSystem
 * @brief System responsible for removing entities that move outside defined bounds.
 *
 * This system requires entities to have both RigidBodyComponent and TransformComponent.
 * It checks the x position of the entity's transform, and if it is outside the range
 * [-400, 2000], it kills the entity and logs the removal.
 */
class CleanSystem : public System{
    public:
     /**
      * @brief Constructs the CleanSystem and sets required components.
      */
     CleanSystem(){
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();

     }
    /**
      * @brief Updates all entities by removing those outside the horizontal bounds.
      *
      * Iterates through system entities and kills those whose x position is
      * greater than 2000 or less than -400, printing a removal message.
      */
    void Update() {
        for(auto entity : GetSystemEntities()){
            auto& transform = entity.GetComponent<TransformComponent>();
            if(transform.position.x > 2000 ||transform.position.x < -400){
                entity.Kill();
                std::cout<<"[CleanSystem] Se elimina entidad "<<entity.GetId()
                <<std::endl;
            }
        }
    }
};

#endif