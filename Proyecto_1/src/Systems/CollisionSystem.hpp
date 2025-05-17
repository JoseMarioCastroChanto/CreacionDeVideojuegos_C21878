#ifndef COLLISIONYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/PolygonColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

#include <glm/glm.hpp>

#include <memory>

class CollisionSystem : public System {
public:
    CollisionSystem() {
        RequireComponent<TransformComponent>();
    }

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
    bool CheckCircleVsCircle(Entity a, Entity b, TransformComponent aTransform, TransformComponent bTransform) {
        auto aCollider = a.GetComponent<CircleColliderComponent>();
        auto bCollider = b.GetComponent<CircleColliderComponent>();

        glm::vec2 aCenterPos = glm::vec2(
                aTransform.position.x - (aCollider.width / 2)* aTransform.scale.x,
                aTransform.position.y - (aCollider.height / 2) * aTransform.scale.x
            );

        glm::vec2 bCenterPos = glm::vec2(
                bTransform.position.x - (bCollider.width / 2) * bTransform.scale.x,
                bTransform.position.y - (bCollider.height / 2)* bTransform.scale.y
            );

        int aRadius = aCollider.radius * aTransform.scale.x;
        int bRadius = bCollider.radius * bTransform.scale.x;

        glm::vec2 dif = aCenterPos - bCenterPos;
        double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));

        int aScale = glm::ceil(aTransform.scale.y);
        if(a.HasComponent<TagProjectileComponent>()){
            aScale=aScale*2;
        }
        int bScale = glm::ceil(bTransform.scale.y);
         if(b.HasComponent<TagProjectileComponent>()){
            bScale=bScale*2;

        }
        
        return (aRadius + bRadius) >= length && aScale == bScale;
    }

    bool IsPointInPolygon(const glm::vec2& point, const std::vector<glm::vec2>& vertices) {
        bool inside = false;
        int count = vertices.size();
        for (int i = 0, j = count - 1; i < count; j = i++) {
            const glm::vec2& vi = vertices[i];
            const glm::vec2& vj = vertices[j];

            if (((vi.y > point.y) != (vj.y > point.y)) &&
                (point.x < (vj.x - vi.x) * (point.y - vi.y) / (vj.y - vi.y) + vi.x)) {
                inside = !inside;
            }
        }
        return inside;
    }

    float DistancePointToSegment(glm::vec2 p, glm::vec2 a, glm::vec2 b) {
        glm::vec2 ab = b - a;
        glm::vec2 ap = p - a;
        float t = glm::dot(ap, ab) / glm::dot(ab, ab);
        t = glm::clamp(t, 0.0f, 1.0f);
        glm::vec2 closest = a + t * ab;
        return glm::length(p - closest);
    }

bool CheckCircleVsPolygon(Entity circleEntity, Entity polygonEntity, TransformComponent circleTransform) {
    auto circleCollider = circleEntity.GetComponent<CircleColliderComponent>();
    auto polygonCollider = polygonEntity.GetComponent<PolygonColliderComponent>();

    glm::vec2 circleCenter = circleTransform.position;

  
    circleCenter.x += (circleCollider.width * circleTransform.scale.x) / 2.0f;
    circleCenter.y += (circleCollider.height * circleTransform.scale.y) / 2.0f;


    float radius = circleCollider.radius * circleTransform.scale.x;

 
    if (IsPointInPolygon(circleCenter,polygonCollider.vertices)) {
        return true;
    }

 
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