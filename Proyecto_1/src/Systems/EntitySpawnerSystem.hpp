#ifndef ENTITYSPAWNERSYSTEM_HPP
#define  ENTITYSPAWNERSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/PolygonColliderComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/EntitySpawnerComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TagWallComponent.hpp"
#include "../Components/TagObjectiveComponent.hpp"
#include "../Components/TagEnemyComponent.hpp"
#include "../Components/TagProjectileComponent.hpp"
#include "../Components/TagPlayerComponent.hpp"
#include "../Components/LifeComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include <sol/sol.hpp>
#include <memory>

class EntitySpawnerSystem : public System{
    private:
    sol::table entities;
    public:
     EntitySpawnerSystem(const std::string& scenePath, sol::state& lua){
        RequireComponent<TransformComponent>();
        RequireComponent<EntitySpawnerComponent>();
         sol::load_result script_result = lua.load_file(scenePath);
            if(!script_result.valid()){
                sol::error err = script_result;
                std::string errMessage = err.what();
                std::cerr<< "[EntitySpawnerSystem]"<< errMessage << std::endl;
                return;

            }      
        lua.script_file(scenePath);
        this->entities = lua["entities"];

     }

    Entity GenerateEntity(std::unique_ptr<Registry>& registry,int idEntity,
     sol::state& lua){
        sol::table entity = entities[idEntity];

        Entity newEntity = registry->CreateEntity();

        sol::optional<sol::table> hasComponents = entity["components"];
        if(hasComponents != sol::nullopt){
            sol::table components = entity["components"];

            //* AnimationComponent
            sol::optional<sol::table>hasAnimation = 
            components["animation"];
            if(hasAnimation != sol::nullopt) {
                newEntity.AddComponent<AnimationComponent>(
                 components["animation"]["numFrames"],
                 components["animation"]["frameSpeedRate"],
                 components["animation"]["isLoop"]
                );
            }

            //* CircleColiderComponent
            sol::optional<sol::table>hasCircleCollider = 
            components["circle_collider"];
            if(hasCircleCollider != sol::nullopt) {
                newEntity.AddComponent<CircleColliderComponent>(
                 components["circle_collider"]["radius"],
                 components["circle_collider"]["width"],
                 components["circle_collider"]["height"]
                );
            }

            //* RigidbodyComponent
            sol::optional<sol::table>hasRigidbody = 
            components["rigidbody"];
            if(hasRigidbody != sol::nullopt) {
                newEntity.AddComponent<RigidBodyComponent>(
                 glm::vec2(
                 components["rigidbody"]["velocity"]["x"],
                 components["rigidbody"]["velocity"]["y"]
                 )
                );
            }

            //* ScriptComponent
            sol::optional<sol::table> hasScript = components["script"];
            if(hasScript != sol::nullopt){
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;

                std::string path = components["script"]["path"];
                lua.script_file(path);

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                newEntity.AddComponent<ScriptComponent>(update, onClick);
            }

            //* Sprite Component
            sol::optional<sol::table>hasSprite = 
            components["sprite"];
            if(hasSprite != sol::nullopt) {
                newEntity.AddComponent<SpriteComponent>(
                 components["sprite"]["assetId"],
                 components["sprite"]["width"],
                 components["sprite"]["height"],
                 components["sprite"]["src_rect"]["x"],
                 components["sprite"]["src_rect"]["y"]
                );
            }
            //* Transform Component
            sol::optional<sol::table>hasTransform = 
            components["transform"];
            if(hasTransform != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                glm::vec2(
                 components["transform"]["position"]["x"],
                 components["transform"]["position"]["y"]
                 ),
                glm::vec2(
                 components["transform"]["scale"]["x"],
                 components["transform"]["scale"]["y"]
                 ),
                 components["transform"]["rotation"]
                );
            }

             //* Depth Component
            sol::optional<sol::table>hasDepth = 
            components["depth"];
            if(hasDepth != sol::nullopt) {
                newEntity.AddComponent<DepthComponent>(
                    components["depth"]["min_scale"],
                    components["depth"]["max_scale"],
                    components["depth"]["original_width"],
                    components["depth"]["scale_speed"], 
                    components["depth"]["reference"]     
                );
            }
             //* TagPlayerComponent
            sol::optional<sol::table>hasTagPlayer = 
            components["tagplayer"];
            if(hasTagPlayer != sol::nullopt) {
                newEntity.AddComponent<TagPlayerComponent>();
            }

               //* TagEnemyComponent
            sol::optional<sol::table>hasTagEnemy = 
            components["tagenemy"];
            if(hasTagEnemy != sol::nullopt) {
                newEntity.AddComponent<TagEnemyComponent>();
            }
             //* TagObjectiveComponent
            sol::optional<sol::table>hasTagObjective = 
            components["tagobjective"];
            if(hasTagObjective != sol::nullopt) {
                newEntity.AddComponent<TagObjectiveComponent>();
            }
            //* TagProjectileComponent
            sol::optional<sol::table>hasTagProjectile = 
            components["tagprojectile"];
            if(hasTagProjectile != sol::nullopt) {
                newEntity.AddComponent<TagProjectileComponent>();
            }

                //* LifeComponent
            sol::optional<sol::table>hasLife = 
            components["life"];
            if(hasLife != sol::nullopt) {
                int args = components["life"]["life_count"];
                int args2 = components["life"]["life_max"];
                newEntity.AddComponent<LifeComponent>(
                    args,args2
                );
            }
              //* DamageComponent
            sol::optional<sol::table>hasDamage = 
            components["damage"];
            if(hasDamage != sol::nullopt) {
                int args = components["damage"]["damage_dealt"];
                newEntity.AddComponent<DamageComponent>(
                    args
                );
            }

        }
        return newEntity;
        
    }
};

#endif