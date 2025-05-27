#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP

/**
 * @file DamageComponent.hpp
 * @brief Defines the DamageComponent which stores damage values.
 */

/**
 * @struct DamageComponent
 * @brief Component that holds the amount of damage dealt.
 */
struct DamageComponent {
    int damage_dealt; /**< The amount of damage dealt by the entity. */

    /**
     * @brief Constructs a new DamageComponent.
     * @param damage_dealt The damage amount (default is 0).
     */
    DamageComponent(int damage_dealt = 0) {
        this->damage_dealt = damage_dealt;
    }
};

#endif
