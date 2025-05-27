#ifndef WALLCOLLISIONSYSTEM_HPP
#define WALLCOLLISIONSYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagWallComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"
#include "../Components/PolygonColliderComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class WallCollisionSystem
 * @brief Handles collisions between wall entities and player entities.
 * 
 * This system requires entities with the TagWallComponent. It listens for collision events
 * and when a player collides with a wall, it adjusts the player's position to prevent
 * overlapping and stops their movement by zeroing velocity.
 */
class WallCollisionSystem : public System {
public:
    /**
     * @brief Constructs WallCollisionSystem and requires TagWallComponent.
     */
    WallCollisionSystem() {
        RequireComponent<TagWallComponent>();
    }
    /**
     * @brief Subscribes this system to the CollisionEvent in the EventManager.
     * @param eventManager Unique pointer reference to the EventManager to subscribe to.
     */
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, WallCollisionSystem>(this,
            &WallCollisionSystem::OnCollision);
    }
    /**
     * @brief Handles a collision event between entities, resolving collisions involving walls and players.
     * 
     * If one entity is a wall and the other a player, adjusts the player's position to avoid overlap
     * and resets the player's velocity.
     * @param e Reference to the CollisionEvent containing involved entities.
     */
    void OnCollision(CollisionEvent& e) {
        bool aIsWall = e.a.HasComponent<TagWallComponent>();
        bool bIsWall = e.b.HasComponent<TagWallComponent>();
        bool aIsPlayer = e.a.HasComponent<TagPlayerComponent>();
        bool bIsPlayer = e.b.HasComponent<TagPlayerComponent>();

        if ((aIsWall || bIsWall) && (aIsPlayer||bIsPlayer)) {
            Entity move = aIsWall ? e.b : e.a;  // Determinamos cuál es la entidad que se mueve

            if (move.HasComponent<TransformComponent>() && move.HasComponent<RigidBodyComponent>()) {
                auto& transform = move.GetComponent<TransformComponent>();
                auto& circleCollider = move.GetComponent<CircleColliderComponent>();
                auto& rigidBody = move.GetComponent<RigidBodyComponent>();
                float radius = circleCollider.radius;

                std::cout << "[WallCollisionSystem] Colisión de la entidad " << e.a.GetId()
                    << " y " << e.b.GetId() << std::endl;

           
                if (rigidBody.velocity.x < 0) {  
                    std::cout << "Colisión desde la derecha, moviendo a la derecha." << std::endl;
                    transform.position.x = e.a.GetComponent<TransformComponent>().position.x + radius;  

                } else if (rigidBody.velocity.x > 0) { 
                    transform.position.x = e.a.GetComponent<TransformComponent>().position.x - radius ;  
                }
                if (rigidBody.velocity.y < 0) { 
                    transform.position.y = e.a.GetComponent<TransformComponent>().position.y + radius;
                } else if (rigidBody.velocity.y > 0) { 
                    transform.position.y = e.a.GetComponent<TransformComponent>().position.y - radius;
                }


                rigidBody.velocity.x = 0;  
                rigidBody.velocity.y = 0;  
            }
        }
    }
};

#endif