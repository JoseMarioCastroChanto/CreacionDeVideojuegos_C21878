#ifndef DEPTHSYSTEM_HPP
#define DEPTHTSYSTEM_HPP

#include "../Components/DepthComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"

#include <glm/glm.hpp>
#include "../ECS/ECS.hpp"

/**
 * @class DepthSystem
 * @brief System to handle the scaling of entities based on their vertical velocity, simulating depth.
 *
 * This system adjusts the scale of entities with DepthComponent, TransformComponent,
 * and RigidBodyComponent to simulate a 3D depth effect by scaling entities smaller when moving up
 * and larger when moving down. It also repositions entities to keep their center stable during scaling.
 */
class DepthSystem : public System{
    public:
    /**
     * @brief Constructor that requires necessary components for the system.
     */
     DepthSystem(){
        RequireComponent<DepthComponent>();
        RequireComponent<TransformComponent>();
         RequireComponent<RigidBodyComponent>();

     }
    /**
     * @brief Updates all entities in the system, adjusting their scale and position based on velocity.
     *
     * If the entity moves upward (negative y velocity), its scale decreases down to a minimum.
     * If it moves downward (positive y velocity), its scale increases up to a maximum.
     * The position is adjusted to maintain the entity's center point during scaling.
     */
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


