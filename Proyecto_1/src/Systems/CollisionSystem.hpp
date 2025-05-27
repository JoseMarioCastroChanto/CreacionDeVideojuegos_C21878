#ifndef COLLISIONYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/PolygonColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

#include <glm/glm.hpp>

#include <memory>

/**
 * @class CollisionSystem
 * @brief System responsible for detecting collisions between entities and emitting collision events.
 * 
 * This system requires entities to have a TransformComponent. It supports collision detection
 * between entities with CircleColliderComponent and PolygonColliderComponent.
 * 
 * The system detects collisions using circle-vs-circle and circle-vs-polygon algorithms.
 * Upon detecting a collision, it emits a CollisionEvent through the EventManager.
 */
class CollisionSystem : public System {
public:
     /**
     * @brief Constructs the CollisionSystem and sets required components.
     */
    CollisionSystem() {
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Updates the system by checking collisions among all entities and emitting events.
     * @param eventManager A unique pointer reference to the EventManager used to emit events.
     *
     * Iterates through all pairs of entities, checks collision conditions (circle vs circle,
     * circle vs polygon), and emits a CollisionEvent if a collision is detected.
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntities();

        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto aTransform = a.GetComponent<TransformComponent>();

            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;
                if (a == b) {
                    continue;
                }
                auto bTransform = b.GetComponent<TransformComponent>();

                bool collision = false;

                bool aHasCircle = a.HasComponent<CircleColliderComponent>();
                bool aHasPolygon = a.HasComponent<PolygonColliderComponent>();
                bool bHasCircle = b.HasComponent<CircleColliderComponent>();
                bool bHasPolygon = b.HasComponent<PolygonColliderComponent>();

                if (aHasCircle && bHasCircle) {
                    collision = CheckCircleVsCircle(a, b, aTransform, bTransform);
                } else if (bHasCircle && aHasPolygon) {
                    collision = CheckCircleVsPolygon(b, a, bTransform);
                } else if (aHasCircle && bHasPolygon) {
                    collision = CheckCircleVsPolygon(a, b, aTransform);
                }

                if (collision) {
                    eventManager->EmitEvent<CollisionEvent>(a, b);
                }
            }
        }
    }

private:
    /**
     * @brief Checks collision between two circle-collider entities.
     * @param a First entity.
     * @param b Second entity.
     * @param aTransform Transform component of first entity.
     * @param bTransform Transform component of second entity.
     * @return True if the two circles collide, false otherwise.
     *
     * Collision is determined by comparing the distance between circle centers
     * with the sum of their radii, and additionally comparing their scale levels.
     */
    bool CheckCircleVsCircle(Entity a, Entity b, TransformComponent aTransform, TransformComponent bTransform) {
        auto aCollider = a.GetComponent<CircleColliderComponent>();
        auto bCollider = b.GetComponent<CircleColliderComponent>();
        auto aDepth = a.GetComponent<DepthComponent>();
        auto bDepth = b.GetComponent<DepthComponent>();

        glm::vec2 aCenterPos = glm::vec2(
                aTransform.position.x - (aCollider.width / 2)* aTransform.scale.x,
                aTransform.position.y - (aCollider.height / 2) * aTransform.scale.y
            );

        glm::vec2 bCenterPos = glm::vec2(
                bTransform.position.x - (bCollider.width / 2) * bTransform.scale.x,
                bTransform.position.y - (bCollider.height / 2)* bTransform.scale.y
            );

        int aRadius = aCollider.radius * aTransform.scale.x;
        int bRadius = bCollider.radius * bTransform.scale.x;

        glm::vec2 dif = aCenterPos - bCenterPos;
        double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));


        int aScale = glm::floor(aTransform.scale.y*10/aDepth.max_scale);
        int bScale = glm::floor(bTransform.scale.y*10/bDepth.max_scale);
        
        return (aRadius + bRadius) >= length && aScale == bScale;
    }

    /**
     * @brief Calculates the shortest distance between point p and line segment ab.
     * @param p The point.
     * @param a Start point of the line segment.
     * @param b End point of the line segment.
     * @return The shortest distance from point p to the segment ab.
     */
    float DistancePointToSegment(glm::vec2 p, glm::vec2 a, glm::vec2 b) {
        glm::vec2 ab = b - a;
        glm::vec2 ap = p - a;
        float t = glm::dot(ap, ab) / glm::dot(ab, ab);
        t = glm::clamp(t, 0.0f, 1.0f);
        glm::vec2 closest = a + t * ab;
        return glm::length(p - closest);
    }
    /**
     * @brief Checks collision between a circle entity and a polygon entity.
     * @param circleEntity Entity with a circle collider.
     * @param polygonEntity Entity with a polygon collider.
     * @param circleTransform Transform component of the circle entity.
     * @return True if the circle collides with the polygon, false otherwise.
     *
     * The collision is determined by checking if the distance from the circle center
     * to any polygon edge is less than or equal to the circle radius.
     */
bool CheckCircleVsPolygon(Entity circleEntity, Entity polygonEntity, TransformComponent circleTransform) {
    auto circleCollider = circleEntity.GetComponent<CircleColliderComponent>();
    auto polygonCollider = polygonEntity.GetComponent<PolygonColliderComponent>();

    glm::vec2 circleCenter = circleTransform.position;

  
    circleCenter.x += (circleCollider.width * circleTransform.scale.x) / 2.0f;
    circleCenter.y += (circleCollider.height * circleTransform.scale.y) / 2.0f;


    float radius = circleCollider.radius * circleTransform.scale.x;
 
    int count = polygonCollider.vertices.size();
    for (int i = 0, j = count - 1; i < count; j = i++) {
        if (DistancePointToSegment(circleCenter, polygonCollider.vertices[j], polygonCollider.vertices[i]) <= radius) {
            return true;
        }
    }


    return false;
}

};

#endif