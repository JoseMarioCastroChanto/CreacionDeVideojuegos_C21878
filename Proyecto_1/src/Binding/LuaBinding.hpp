#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
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

// TransformComponent
void SetScale(Entity entity, float x, float y) {
     auto& transform = entity.GetComponent<TransformComponent>();
     transform.scale.x = x;
     transform.scale.y = y;
}

void SetPosition(Entity entity, float x, float y) {
     auto& transform = entity.GetComponent<TransformComponent>();
     transform.position.x = x;
     transform.position.y = y;
}

float GetPositionX(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.position.x;
}
float GetPositionY(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.position.y;
}

// SpriteComponent
void SetSrcRect(Entity entity,int width = 0
    , int height = 0, int srcRectX = 0, int srcRectY = 0){
    auto& sprite = entity.GetComponent<SpriteComponent>();
    sprite.srcRect = {srcRectX, srcRectY, width, height};
}

//AnimationComponent
void SetNumFrames(Entity entity,int numFrames){
    auto& animation = entity.GetComponent<AnimationComponent>();
    animation.numFrames = numFrames;

}


// Scenes
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif