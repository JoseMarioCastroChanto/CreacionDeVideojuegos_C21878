#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Component to represent the transform of an entity.
 * 
 * Contains position, scale, and rotation.
 */
struct TransformComponent {
    glm::vec2 position;  ///< Position of the entity in 2D space
    glm::vec2 scale;     ///< Scale factors on the x and y axes
    double rotation;     ///< Rotation angle in degrees or radians (depending on use)

    /**
     * @brief Constructor for TransformComponent.
     * 
     * @param position Initial position (default is (0,0))
     * @param scale Initial scale (default is (1,1))
     * @param rotation Initial rotation (default is 0)
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                       glm::vec2 scale = glm::vec2(1.0, 1.0), 
                       double rotation = 0.0) {
      this->position = position;
      this->scale = scale;
      this->rotation = rotation;
    }
};

#endif
