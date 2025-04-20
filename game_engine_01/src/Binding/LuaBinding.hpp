#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

//Controles

bool IsActionActivated(const std::string& action){
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// RigidBodyComponent
void SetVelocity(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.velocity.x = x;
    rigidbody.velocity.y = y;
}

// Scenes
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif