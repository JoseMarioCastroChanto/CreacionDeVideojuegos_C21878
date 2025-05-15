#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Systems/EntitySpawnerSystem.hpp"
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

int GetVelocity(Entity entity){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    return rigidbody.velocity.x;
}

// TransformComponent
float GetScale(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.scale.x;
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

//EntitySpawnerComponent
void CreateBomb(Entity entity, int dir){
    auto& transform = entity.GetComponent<TransformComponent>();
    Entity newBomb = Game::GetInstance().registry->GetSystem<EntitySpawnerSystem>().GenerateEntity(
        Game::GetInstance().registry,0,Game::GetInstance().lua
    );
    auto& transformBomb = newBomb.GetComponent<TransformComponent>();
    auto& rigidBodyBomb = newBomb.GetComponent<RigidBodyComponent>();
    transformBomb.position = transform.position;
    transformBomb.scale.x = transform.scale.x/2;
    transformBomb.scale.y = transform.scale.y/2;
    rigidBodyBomb.velocity.x = rigidBodyBomb.velocity.x*(transformBomb.scale.x/2)*dir;

}


// Scenes
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif