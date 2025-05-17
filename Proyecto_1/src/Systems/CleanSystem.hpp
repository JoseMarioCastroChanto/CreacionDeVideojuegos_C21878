#ifndef CLEANSYSTEM_HPP
#define CLEANTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class CleanSystem : public System{
    public:
     CleanSystem(){
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();

     }

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