#ifndef ENTITYSPAWNERCOMPONENT_HPP
#define ENTITYSPAWNERCOMPONENT_HPP

/**
 * @file EntitySpawnerComponent.hpp
 * @brief Component to indicate if an entity is a player spawner.
 */

/**
 * @struct EntitySpawnerComponent
 * @brief Component that marks an entity as a player or non-player spawner.
 */
struct EntitySpawnerComponent {
    bool is_player; /**< Flag to indicate if this spawner is for the player (true) or not (false). */

    /**
     * @brief Construct a new EntitySpawnerComponent.
     * 
     * @param is_player Boolean indicating if spawner is for player (default false).
     */
    EntitySpawnerComponent(bool is_player = false) {
        this->is_player = is_player;
    }
};

#endif
