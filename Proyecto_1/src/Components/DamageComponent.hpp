#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP

struct DamageComponent {
    int damage_dealt;  

    DamageComponent( int damage_dealt = 0){
        this->damage_dealt = damage_dealt;
    }

};

#endif