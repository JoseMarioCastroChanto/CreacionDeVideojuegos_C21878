#ifndef POLYGONCOLLIDERCOMPONENT_HPP
#define POLYGONCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>
#include <vector>

struct PolygonColliderComponent {
    std::vector<glm::vec2> vertices;
       
    PolygonColliderComponent( std::vector<glm::vec2> vertices = {}){
        this->vertices = vertices;
    }
};

#endif