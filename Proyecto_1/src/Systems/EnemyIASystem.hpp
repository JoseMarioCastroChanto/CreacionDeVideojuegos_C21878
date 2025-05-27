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

/**
 * @class EnemyIASystem
 * @brief System responsible for enemy AI logic, specifically searching for closest objectives.
 *
 * This system provides functionality to find the closest objective to an enemy entity,
 * optionally including or excluding player entities.
 */
class EnemyIASystem : public System{
    public:
    /**
     * @brief Constructor requiring the TransformComponent.
     */
     EnemyIASystem(){
        RequireComponent<TransformComponent>();

     }

    /**
     * @brief Finds the closest objective's TransformComponent relative to the enemy.
     * 
     * @param enemy The enemy entity performing the search.
     * @param isPlayerIncl Whether to include player entities as objectives.
     * @return TransformComponent of the closest objective found.
     */
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
        if (isPlayerIncl && entity.HasComponent<TagPlayerComponent>()) {
           const auto& targetTransform = entity.GetComponent<TransformComponent>();
            closestTransform = targetTransform;
            break; 
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

    /**
     * @brief Finds the closest objective's DepthComponent relative to the enemy.
     * 
     * @param enemy The enemy entity performing the search.
     * @param isPlayerIncl Whether to include player entities as objectives.
     * @return DepthComponent of the closest objective found.
     */
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
         if (isPlayerIncl && entity.HasComponent<TagPlayerComponent>()) {
            const auto& targetDepth = entity.GetComponent<DepthComponent>();
            closestDepth = targetDepth;
            break; 
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