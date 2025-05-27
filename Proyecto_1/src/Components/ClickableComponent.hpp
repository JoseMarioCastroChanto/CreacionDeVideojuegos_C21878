#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @file ClickableComponent.hpp
 * @brief Defines the ClickableComponent to track if an entity was clicked.
 */

/**
 * @struct ClickableComponent
 * @brief Component that indicates if an entity has been clicked.
 */
struct ClickableComponent {
    bool isClicked; /**< True if the entity has been clicked, false otherwise. */

    /**
     * @brief Constructs a new ClickableComponent with isClicked initialized to false.
     */
    ClickableComponent(){
        isClicked = false;
    }
};

#endif
