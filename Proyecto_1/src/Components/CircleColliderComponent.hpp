#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

struct CircleColliderComponent{
 double radius;
 double width;
 double height;

 CircleColliderComponent(double radius = 0,double width = 0,double height = 0){
    this->radius = radius;
    this->width = width;
    this->height = height;
 }

};
#endif