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

class WallCollisionSystem : public System {
public:
    WallCollisionSystem() {
        RequireComponent<TagWallComponent>();
    }

    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, WallCollisionSystem>(this,
            &WallCollisionSystem::OnCollision);
    }

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