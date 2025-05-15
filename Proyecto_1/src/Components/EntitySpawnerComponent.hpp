#ifndef ENTITYSPAWNERCOMPONENT_HPP
#define ENTITYSPAWNERCOMPONENT_HPP


struct EntitySpawnerComponent{
    bool is_player;  
 
    EntitySpawnerComponent(bool is_player = 0){
        this->is_player = is_player;
    }
};
#endif