#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @file CircleColliderComponent.hpp
 * @brief Defines the CircleColliderComponent used for circular collision detection.
 */

/**
 * @struct CircleColliderComponent
 * @brief Component that defines the properties of a circular collider.
 */
struct CircleColliderComponent {
    double radius;  /**< The radius of the circular collider. */
    double width;   /**< The width of the bounding box (optional, for non-perfect circles). */
    double height;  /**< The height of the bounding box (optional, for non-perfect circles). */

    /**
     * @brief Constructs a new CircleColliderComponent.
     * @param radius Radius of the circular collider. Default is 0.
     * @param width Width of the bounding box. Default is 0.
     * @param height Height of the bounding box. Default is 0.
     */
    CircleColliderComponent(double radius = 0, double width = 0, double height = 0) {
        this->radius = radius;
        this->width = width;
        this->height = height;
    }
};

#endif
