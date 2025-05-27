#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"


/**
 * @class MovementSystem
 * @brief System responsible for updating entity positions based on their velocity.
 * 
 * This system requires entities to have both RigidBodyComponent and TransformComponent.
 * It updates the position of each entity every frame according to its velocity and the elapsed time.
 */
class MovementSystem : public System{
    public:
    /**
     * @brief Constructs a MovementSystem and requires RigidBodyComponent and TransformComponent.
     */
     MovementSystem(){
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();

     }
    /**
     * @brief Updates the position of each entity based on its velocity and the delta time.
     * 
     * @param dt The delta time (time elapsed since last update), used to scale velocity.
     * 
     * For each entity:
     * - Retrieves the velocity from the RigidBodyComponent.
     * - Updates the position in the TransformComponent by velocity * dt.
     */
    void Update(double dt) {
        for(auto entity : GetSystemEntities()){
            const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();

            transform.position.x += rigidbody.velocity.x * dt;
            transform.position.y += rigidbody.velocity.y * dt;
        }
    }
};

#endif