#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

struct LifeComponent {
    int life_count;  

    LifeComponent( int life_count = 0){
        this->life_count = life_count;
    }

};

#endif