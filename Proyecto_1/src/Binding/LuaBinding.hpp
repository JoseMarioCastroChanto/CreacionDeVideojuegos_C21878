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
#include "../Systems/DamageSystem.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"


/**
 * @file LuaBinding.hpp
 * @brief Contains Lua bindings for interacting with ECS components and systems.
 */

//Controls

/**
 * @brief Checks if a specific action is currently activated in the controller.
 * @param action The action name.
 * @return True if the action is activated, false otherwise.
 */
bool IsActionActivated(const std::string& action){
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// RigidBodyComponent

/**
 * @brief Sets the velocity of an entity's RigidBodyComponent.
 * @param entity The target entity.
 * @param x Velocity in x-axis.
 * @param y Velocity in y-axis.
 */
void SetVelocity(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.velocity.x = x;
    rigidbody.velocity.y = y;
}

/**
 * @brief Gets the horizontal velocity (x) of an entity's RigidBodyComponent.
 * @param entity The target entity.
 * @return The x velocity.
 */
int GetVelocity(Entity entity){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    return rigidbody.velocity.x;
}

/**
 * @brief Gets the horizontal scale of an entity's TransformComponent.
 * @param entity The target entity.
 * @return The scale on the x-axis.
 */

// TransformComponent

/**
 * @brief Gets the horizontal scale of an entity's TransformComponent.
 * @param entity The target entity.
 * @return The scale on the x-axis.
 */
float GetScale(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.scale.x;
}

/**
 * @brief Sets the scale of an entity's TransformComponent.
 * @param entity The target entity.
 * @param x Scale on the x-axis.
 * @param y Scale on the y-axis.
 */
void SetScale(Entity entity, float x, float y) {
     auto& transform = entity.GetComponent<TransformComponent>();
     transform.scale.x = x;
     transform.scale.y = y;
}

/**
 * @brief Sets the position of an entity's TransformComponent.
 * @param entity The target entity.
 * @param x Position on the x-axis.
 * @param y Position on the y-axis.
 */
void SetPosition(Entity entity, float x, float y) {
     auto& transform = entity.GetComponent<TransformComponent>();
     transform.position.x = x;
     transform.position.y = y;
}

/**
 * @brief Gets the x position of an entity's TransformComponent.
 * @param entity The target entity.
 * @return The x position.
 */
float GetPositionX(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.position.x;
}

/**
 * @brief Gets the y position of an entity's TransformComponent.
 * @param entity The target entity.
 * @return The y position.
 */
float GetPositionY(Entity entity) {
     auto& transform = entity.GetComponent<TransformComponent>();
     return transform.position.y;
}

// DepthComponent

/**
 * @brief Gets the max depth scale from an entity's DepthComponent.
 * @param entity The target entity.
 * @return The max depth scale.
 */
double GetDepth(Entity entity){
    auto& depth = entity.GetComponent<DepthComponent>();
    return depth.max_scale;
}

// SpriteComponent

/**
 * @brief Sets the source rectangle for the SpriteComponent of an entity.
 * @param entity The target entity.
 * @param width Width of the source rect.
 * @param height Height of the source rect.
 * @param srcRectX X offset of the source rect.
 * @param srcRectY Y offset of the source rect.
 */
void SetSrcRect(Entity entity,int width = 0
    , int height = 0, int srcRectX = 0, int srcRectY = 0){
    auto& sprite = entity.GetComponent<SpriteComponent>();
    sprite.srcRect = {srcRectX, srcRectY, width, height};
}

//AnimationComponent

/**
 * @brief Sets the number of frames for the AnimationComponent of an entity.
 * @param entity The target entity.
 * @param numFrames Number of animation frames.
 */
void SetNumFrames(Entity entity,int numFrames){
    auto& animation = entity.GetComponent<AnimationComponent>();
    animation.numFrames = numFrames;

}

//EntitySpawnerComponent


/**
 * @brief Creates a new entity using the EntitySpawnerSystem and initializes its position and velocity.
 * @param entity The source entity.
 * @param dir Direction multiplier for velocity.
 * @param num Identifier for the entity type.
 * @param scale Scale to apply to the new entity.
 */
void CreateDynamicEntity(Entity entity, double dir, int num, double scale){
    auto& transform = entity.GetComponent<TransformComponent>();
    Entity newEntity = Game::GetInstance().registry->GetSystem<EntitySpawnerSystem>().GenerateEntity(
        Game::GetInstance().registry,num,Game::GetInstance().lua
    );
    if(scale > 0){
        auto& transformNew = newEntity.GetComponent<TransformComponent>();
        auto& rigidBodyNew= newEntity.GetComponent<RigidBodyComponent>();
        transformNew.position = transform.position;
        transformNew.scale.x = scale;
        transformNew.scale.y = scale;
        rigidBodyNew.velocity.x = rigidBodyNew.velocity.x*dir;}
  

}

//Time


/**
 * @brief Gets the delta time of the current scene from SceneTimeSystem.
 * @return Delta time in milliseconds.
 */
int GetDeltaTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetDeltaTime();
    return time;
}

/**
 * @brief Gets the total scene time from SceneTimeSystem.
 * @return Scene time in milliseconds.
 */
int GetTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetSceneTime();
    return time;
}

/**
 * @brief Sets a timer text value in a TextComponent from the given time.
 * @param entity The target entity.
 * @param newTime New time value in milliseconds.
 */
void SetTimer(Entity entity, int newTime){
    std::string timer = std::to_string(newTime / 1000);
    entity.GetComponent<TextComponent>().text = timer;
    
}

//Defeat 

/**
 * @brief Checks whether the defeat condition has been triggered.
 * @return True if defeat is active, false otherwise.
 */
bool GetDefeat(){
    return Game::GetInstance().registry->GetSystem<DefeatSystem>().Defeat;
}

//Text

/**
 * @brief Sets the text of a TextComponent using an integer value.
 * @param entity The target entity.
 * @param newText Integer value to set as text.
 */
void SetText(Entity entity, int newText){
    entity.GetComponent<TextComponent>().text = std::to_string(newText);
    
}

// Scenes

/**
 * @brief Switches to a different scene by name.
 * @param sceneName Name of the next scene.
 */
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

//EnemyIASystem

/**
 * @brief Searches for the nearest target entity and returns its X position.
 * @param entity The querying entity.
 * @param player Whether to search for a player (true) or enemy (false).
 * @return The X position of the closest objective.
 */
double SearchObjectiveX(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.position.x;
}

/**
 * @brief Searches for the nearest target entity and returns its Y position.
 * @param entity The querying entity.
 * @param player Whether to search for a player (true) or enemy (false).
 * @return The Y position of the closest objective.
 */
double SearchObjectiveY(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.position.y;
}

/**
 * @brief Searches for the nearest target entity and returns its scale.
 * @param entity The querying entity.
 * @param player Whether to search for a player (true) or enemy (false).
 * @return The scale of the closest objective.
 */
double SearchObjectiveScale(Entity entity, bool player){
    TransformComponent transform = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjective(entity,player);
    return transform.scale.x;
}

/**
 * @brief Searches for the nearest target entity and returns its depth.
 * @param entity The querying entity.
 * @param player Whether to search for a player (true) or enemy (false).
 * @return The depth of the closest objective.
 */
double SearchObjectiveDepth(Entity entity, bool player){
    DepthComponent depth = Game::GetInstance().registry->GetSystem<EnemyIASystem>().SearchClosestObjectiveDepth(entity,player);
    return depth.max_scale;
}

// Damage System

/**
 * @brief Destroys all enemy entities via the DamageSystem.
 */
void DestroyAllEnemies(){
    Game::GetInstance().registry->GetSystem<DamageSystem>().DestroyAllEnemies();
}

//Kill entity

/**
 * @brief Marks an entity as killed.
 * @param entity The entity to kill.
 */
void Kill(Entity entity){
    entity.Kill();
}
#endif