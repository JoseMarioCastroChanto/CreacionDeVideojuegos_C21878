#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @file RigidBodyComponent.hpp
 * @brief Component representing a rigid body's velocity.
 */

/**
 * @struct RigidBodyComponent
 * @brief Stores the velocity vector of an entity's rigid body.
 */
struct RigidBodyComponent{
    glm::vec2 velocity; /**< Velocity vector (x, y) of the rigid body */

    /**
     * @brief Construct a new RigidBodyComponent object.
     * 
     * @param velocity Initial velocity vector (default is zero vector).
     */
    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0)){
        this->velocity = velocity;
    }
};

#endif
