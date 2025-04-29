#ifndef DEPTHCOMPONENT_HPP
#define DEPTHCOMPONENT_HPP
#include <glm/glm.hpp>

struct DepthComponent {
    float min_scale;  
    float max_scale; 
    float original_width;
    float scale_speed;
    float reference_point;

    DepthComponent( float min_scale = 0, float max_scale = 0, 
    float original_width = 0, float scale_speed = 0, 
    float reference_point = 0){
        this->min_scale = min_scale;
        this->max_scale = max_scale;
        this->original_width = original_width;
        this->scale_speed = scale_speed;
        this->reference_point = reference_point;
    }
};
#endif