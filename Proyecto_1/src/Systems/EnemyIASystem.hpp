#ifndef ENEMYIASYSTEM_HPP
#define ENEMYIASYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../Components/TagEnemyComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"
#include "../ECS/ECS.hpp"
#include <glm/glm.hpp>

class EnemyIASystem : public System{
    public:
     EnemyIASystem(){
        RequireComponent<TransformComponent>();

     }

TransformComponent SearchClosestObjective(Entity enemy, bool isPlayerIncl) {
    const auto& enemyTransform = enemy.GetComponent<TransformComponent>();
    glm::vec2 enemyPos = enemyTransform.position;

    double minDistance = std::numeric_limits<double>::max();
    TransformComponent closestTransform;

    for (auto entity : GetSystemEntities()) {
        if (!entity.HasComponent<TagObjectiveComponent>()) continue;

        if (!isPlayerIncl && entity.HasComponent<TagPlayerComponent>()) {
            continue;
        }

        const auto& targetTransform = entity.GetComponent<TransformComponent>();
        glm::vec2 targetPos = targetTransform.position;

        double distance = glm::distance(enemyPos, targetPos);

        if (distance < minDistance) {
            minDistance = distance;
            closestTransform = targetTransform;
        }
    }

    return closestTransform; 
}

DepthComponent SearchClosestObjectiveDepth(Entity enemy, bool isPlayerIncl) {
    const auto& enemyTransform = enemy.GetComponent<TransformComponent>();
    glm::vec2 enemyPos = enemyTransform.position;

    double minDistance = std::numeric_limits<double>::max();
    DepthComponent closestDepth;

    for (auto entity : GetSystemEntities()) {
        if (!entity.HasComponent<TagObjectiveComponent>()) continue;

        if (!isPlayerIncl && entity.HasComponent<TagPlayerComponent>()) {
            continue;
        }

        const auto& targetTransform = entity.GetComponent<TransformComponent>();
        const auto& targetDepth = entity.GetComponent<DepthComponent>();
        glm::vec2 targetPos = targetTransform.position;

        double distance = glm::distance(enemyPos, targetPos);

        if (distance < minDistance) {
            minDistance = distance;
            closestDepth = targetDepth;
        }
    }

    return closestDepth; 
}
};

#endif