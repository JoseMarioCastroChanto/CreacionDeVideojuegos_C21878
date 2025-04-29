#ifndef DEPTHSYSTEM_HPP
#define DEPTHTSYSTEM_HPP

#include "../Components/DepthComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"

#include <glm/glm.hpp>
#include "../ECS/ECS.hpp"

class DepthSystem : public System{
    public:
     DepthSystem(){
        RequireComponent<DepthComponent>();
        RequireComponent<TransformComponent>();
         RequireComponent<RigidBodyComponent>();

     }
void Update() {
    for(auto entity : GetSystemEntities()){
        auto& depth = entity.GetComponent<DepthComponent>();
        auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
        auto& transform = entity.GetComponent<TransformComponent>();

        float previous_scale = transform.scale.y;
        float current_scale = previous_scale;
        
        if(rigidBody.velocity.y < 0) {
            // Movimiento hacia arriba = pequeno
            current_scale = glm::max(depth.min_scale, current_scale - depth.scale_speed);
        }
        else if(rigidBody.velocity.y > 0) {
            // Movimiento hacia abajo = grande
            current_scale = glm::min(depth.max_scale, current_scale + depth.scale_speed);
        }
        
        if(current_scale != previous_scale) {
            // Reposicionar para mantener el centro
            float width_diff = depth.original_width * (current_scale - previous_scale);
            transform.position.x -= (width_diff / 2.0f);

            transform.scale.x = current_scale;
            transform.scale.y = current_scale;
        }
    }
}
};

#endif


