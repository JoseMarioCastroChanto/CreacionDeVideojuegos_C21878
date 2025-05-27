#ifndef DEPTHCOMPONENT_HPP
#define DEPTHCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @file DepthComponent.hpp
 * @brief Defines the DepthComponent for handling scaling and depth effects.
 */

/**
 * @struct DepthComponent
 * @brief Component that manages depth-related scaling parameters for an entity.
 */
struct DepthComponent {
    float min_scale;       /**< Minimum scale value for depth effect. */
    float max_scale;       /**< Maximum scale value for depth effect. */
    float original_width;  /**< Original width of the entity before scaling. */
    float scale_speed;     /**< Speed at which scaling changes over time. */
    float reference_point; /**< Reference point used for depth calculation. */

    /**
     * @brief Constructs a new DepthComponent.
     * 
     * @param min_scale Minimum scale value (default 0).
     * @param max_scale Maximum scale value (default 0).
     * @param original_width Original width before scaling (default 0).
     * @param scale_speed Speed of scale changes (default 0).
     * @param reference_point Reference point for depth (default 0).
     */
    DepthComponent(float min_scale = 0, float max_scale = 0, 
                   float original_width = 0, float scale_speed = 0, 
                   float reference_point = 0) {
        this->min_scale = min_scale;
        this->max_scale = max_scale;
        this->original_width = original_width;
        this->scale_speed = scale_speed;
        this->reference_point = reference_point;
    }
};
#endif
