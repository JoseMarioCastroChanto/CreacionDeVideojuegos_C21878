#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @brief Represents a mouse click event.
 */
class ClickEvent : public Event {
    public:
    int buttonCode;  ///< Code of the mouse button clicked.
    int posX;       ///< X position of the mouse click.
    int posY;       ///< Y position of the mouse click.

     /**
     * @brief Constructs a ClickEvent with optional button code and position.
     * @param buttonCode Code of the button clicked (default 0).
     * @param posX X coordinate of the click (default 0).
     * @param posY Y coordinate of the click (default 0).
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0){
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};

#endif