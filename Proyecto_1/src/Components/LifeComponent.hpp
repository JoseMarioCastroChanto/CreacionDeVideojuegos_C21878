#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

struct LifeComponent {
    int life_count; 
    int life_max; 

    LifeComponent( int life_count = 0, int life_max = 0){
        this->life_count = life_count;
        this->life_max = life_max;
    }

};

#endif