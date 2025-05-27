#ifndef LIFECOMPONENT_HPP
#define LIFECOMPONENT_HPP

/**
 * @file LifeComponent.hpp
 * @brief Component to manage an entity's life count and maximum life.
 */

/**
 * @struct LifeComponent
 * @brief Represents the current and maximum life of an entity.
 */
struct LifeComponent {
    int life_count; /**< Current life count of the entity. */
    int life_max;   /**< Maximum life the entity can have. */

    /**
     * @brief Construct a new LifeComponent object.
     * 
     * @param life_count Initial life count (default 0).
     * @param life_max Maximum life count (default 0).
     */
    LifeComponent(int life_count = 0, int life_max = 0) {
        this->life_count = life_count;
        this->life_max = life_max;
    }
};

#endif
