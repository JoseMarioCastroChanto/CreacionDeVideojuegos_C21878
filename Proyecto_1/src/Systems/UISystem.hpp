#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <iostream>

#include "../Components/ClickableComponent.hpp"

#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

/**
 * @class UISystem
 * @brief Handles UI elements that can be clicked and processes click events.
 * 
 * This system requires entities to have ClickableComponent, TextComponent, and TransformComponent.
 * It subscribes to click events and triggers Lua script callbacks when UI elements are clicked.
 */
class UISystem : public System {
    public:
    /**
     * @brief Constructs UISystem and requires necessary components.
     */
    UISystem(){
        RequireComponent<ClickableComponent>();
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }
    /**
     * @brief Subscribes this system to the ClickEvent in the EventManager.
     * @param eventManager Unique pointer reference to the EventManager to subscribe to.
     */
    void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager){
        eventManager->SubscribeToEvent<ClickEvent, UISystem>(this, 
        &UISystem::OnClickEvent);
    }
    /**
     * @brief Handles a ClickEvent by checking if the click position intersects with any UI element.
     * 
     * If an entity contains a ScriptComponent with an onClick Lua callback, it will be called.
     * @param e Reference to the ClickEvent containing click position data.
     */
    void OnClickEvent(ClickEvent& e){
        for(auto entity : GetSystemEntities()){
            const auto& text = entity.GetComponent<TextComponent>();
            const auto& transform = entity.GetComponent<TransformComponent>();

            if(transform.position.x < e.posX
            && e.posX < transform.position.x + text.width
            && transform.position.y < e.posY
            && e.posY < transform.position.y + text.height){
             if(entity.HasComponent<ScriptComponent>()){
                const auto& script = entity.GetComponent<ScriptComponent>();
                if(script.onClick != sol::nil){
                    script.onClick();
                }
             }
            }
        }
    }
};

#endif