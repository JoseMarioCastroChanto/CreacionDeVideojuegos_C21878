#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Systems/EntitySpawnerSystem.hpp"
#include "../Systems/SceneTimeSystem.hpp"
#include "../Systems/DefeatSystem.hpp"
#include "../Systems/EnemyIASystem.hpp"
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

//EntitySpawnerComponent
void CreateDynamicEntity(Entity entity, double dir, int num, double scale){
    auto& transform = entity.GetComponent<TransformComponent>();
    Entity newEntity = Game::GetInstance().registry->GetSystem<EntitySpawnerSystem>().GenerateEntity(
        Game::GetInstance().registry,num,Game::GetInstance().lua
    );
    auto& transformNew = newEntity.GetComponent<TransformComponent>();
    auto& rigidBodyNew= newEntity.GetComponent<RigidBodyComponent>();
    transformNew.position = transform.position;
    transformNew.scale.x = scale;
    transformNew.scale.y = scale;
    rigidBodyNew.velocity.x = rigidBodyNew.velocity.x*dir;
  

}

//Time
int GetDeltaTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetDeltaTime();
    return time;
}
int GetTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetSceneTime();
    return time;
}
void SetTimer(Entity entity, int newTime){
    std::string timer = std::to_string(newTime / 1000);
    entity.GetComponent<TextComponent>().text = timer;
    
}

//Defeat 
bool GetDefeat(){
    return Game::GetInstance().registry->GetSystem<DefeatSystem>().Defeat;
}

//Text
void SetText(Entity entity, int newText){
    entity.GetComponent<TextComponent>().text = std::to_string(newText);
    
}

// Scenes
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

//EnemyIASystem
double SearchObjectiveX(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.position.x;
}

double SearchObjectiveY(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.position.y;
}

double SearchObjectiveScale(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.scale.x;
}

double SearchObjectiveDepth(Entity entity, bool player){
    DepthComponent depth = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjectiveDepth(entity,player);
    return depth.max_scale;
}
#endif