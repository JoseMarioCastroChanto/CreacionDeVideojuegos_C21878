#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @file ScriptComponent.hpp
 * @brief Component to hold Lua script functions for entity behavior.
 */

/**
 * @struct ScriptComponent
 * @brief Holds Lua functions for updating and click handling scripts.
 */
struct ScriptComponent {
    sol::function update;   /**< Lua function called every frame to update entity */
    sol::function onClick;  /**< Lua function called when the entity is clicked */

    /**
     * @brief Construct a new ScriptComponent object.
     * 
     * @param update Lua function for updating the entity (default nil).
     * @param onClick Lua function for click event handling (default nil).
     */
    ScriptComponent(sol::function update = sol::lua_nil, 
                    sol::function onClick = sol::lua_nil){
        this->update = update;
        this->onClick = onClick;
    }
};

#endif
