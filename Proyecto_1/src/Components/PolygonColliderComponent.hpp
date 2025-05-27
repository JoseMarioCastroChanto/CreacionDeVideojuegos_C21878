#ifndef POLYGONCOLLIDERCOMPONENT_HPP
#define POLYGONCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>
#include <vector>

/**
 * @file PolygonColliderComponent.hpp
 * @brief Component that holds polygon collider vertices for collision detection.
 */

/**
 * @struct PolygonColliderComponent
 * @brief Stores the vertices that define a polygon collider shape.
 */
struct PolygonColliderComponent {
    std::vector<glm::vec2> vertices; /**< List of vertices that form the polygon collider. */

    /**
     * @brief Construct a new PolygonColliderComponent object.
     * 
     * @param vertices Vector of 2D points representing the polygon vertices (default empty).
     */
    PolygonColliderComponent(std::vector<glm::vec2> vertices = {}) {
        this->vertices = vertices;
    }
};

#endif
