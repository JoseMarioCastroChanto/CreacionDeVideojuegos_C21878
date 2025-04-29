#include "SceneLoader.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/PolygonColliderComponent.hpp"
#include "../Components/DepthComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TagWallComponent.hpp"

SceneLoader::SceneLoader(){
     std::cout<< "[SceneLoader] Se ejecuta constructor" << std::endl;
}

SceneLoader:: ~SceneLoader(){
     std::cout<< "[SceneLoader] Se ejecuta destructor" << std::endl;
}

void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer){
  
  sol::load_result script_result = lua.load_file(scenePath);
  if(!script_result.valid()){
    sol::error err = script_result;
    std::string errMessage = err.what();
    std::cerr<< "[SceneLoader]"<< errMessage << std::endl;
    return;

  }

  lua.script_file(scenePath);
  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  LoadSprites(renderer, sprites, assetManager);

  sol::table fonts = scene["fonts"];
  LoadFonts(fonts, assetManager);

  sol::table keys = scene["keys"];
  LoadKeys(keys, controllerManager);

  sol::table buttons = scene["buttons"];
  LoadButtons(buttons, controllerManager);

  sol::table entities = scene["entities"];
  LoadEntities(lua, entities, registry);

}

void  SceneLoader::LoadSprites(SDL_Renderer* renderer, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager){
    int index = 0;
    while (true){
        sol::optional<sol::table> hasSprite = sprites [index];
        if(hasSprite == sol::nullopt){
            break;
        }

        sol::table sprite = sprites[index];

        std::string assetId = sprite["assetId"];
        std::string filePath = sprite["filePath"];

        assetManager->AddTexture(renderer, assetId, filePath);

        index++;
    }

}

void SceneLoader::LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager){
  int index = 0;
  while(true){
    sol::optional<sol::table> hasFont = fonts[index];
    if(hasFont == sol::nullopt){
        break;
    }

    sol::table font = fonts[index];
    std::string fontId = font["fontId"];
    std::string filePath = font["filePath"];
    int size = font["fontSize"];

    assetManager->AddFont(fontId, filePath, size);

    index++;
  }
}

void  SceneLoader::LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& 
  controllerManager){
     int index = 0;
    while (true){
        sol::optional<sol::table> hasKey = keys[index];
        if(hasKey == sol::nullopt){
            break;
        }

        sol::table key = keys[index];

        std::string name = key ["name"];
        int keyCode = key["key"];

        controllerManager->AddActionKey(name, keyCode);

        index++;

    }
  }

void SceneLoader::LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& 
  controllerManager){
        int index = 0;
    while (true){
        sol::optional<sol::table> hasButtons = buttons[index];
        if(hasButtons == sol::nullopt){
            break;
        }

        sol::table button = buttons[index];

        std::string name = button ["name"];
        int buttonCode = button["button"];

        controllerManager->AddMouseButton(name, buttonCode);

        index++;

    }

  }

void  SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities, 
  std::unique_ptr<Registry>& registry){
    int index = 0;
    while (true){
        sol::optional<sol::table> hasEntity = entities [index];
        if(hasEntity == sol::nullopt){
            break;
        }

        sol::table entity = entities[index];

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

             //* PolygonColliderComponent

             sol::optional<sol::table> hasPolygonCollider = components["polygon_collider"];
                if (hasPolygonCollider != sol::nullopt) {
                    std::vector<glm::vec2> vertices;
                     for (size_t i = 0; i <= hasPolygonCollider->size(); i++) {
                        auto vertex = (*hasPolygonCollider)[i];
                        glm::vec2 point = {
                            vertex["x"],
                            vertex["y"]
                        };
                        vertices.push_back(point);
                    }       
                    newEntity.AddComponent<PolygonColliderComponent>(vertices);
                }
          
             //* TagWallComponent
            sol::optional<sol::table>hasTagWall = 
            components["tagwall"];
            if(hasTagWall != sol::nullopt) {
                newEntity.AddComponent<TagWallComponent>();
            }

            //* ClickableComponent
            sol::optional<sol::table>hasClickable = 
            components["clickable"];
            if(hasClickable != sol::nullopt) {
                newEntity.AddComponent<ClickableComponent>();
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
            //* Text Component
            sol::optional<sol::table>hasText = components["text"];
            if(hasText != sol::nullopt){
                newEntity.AddComponent<TextComponent>(
                    components["text"]["text"],
                    components["text"]["fontId"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"]
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
        }

        index++;

    }
  }