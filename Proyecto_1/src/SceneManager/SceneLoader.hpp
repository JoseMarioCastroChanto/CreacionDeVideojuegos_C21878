#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Loads a game scene from a Lua script.
 * 
 * This class is responsible for parsing Lua scripts to load game assets, 
 * entities, key and button bindings, and music into the appropriate managers 
 * and systems (AssetManager, ControllerManager, Registry, etc.).
 */
class SceneLoader {
  private:
    /**
     * @brief Loads sprite assets from Lua table into the AssetManager.
     * @param render SDL renderer used for texture creation.
     * @param sprites Lua table containing sprite definitions.
     * @param assetManager Unique pointer to the AssetManager instance.
     */
  void LoadSprites(SDL_Renderer* render, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads font assets from Lua table into the AssetManager.
     * @param fonts Lua table containing font definitions.
     * @param assetManager Unique pointer to the AssetManager instance.
     */
   void LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager);
  
    /**
     * @brief Loads key bindings from Lua table into the ControllerManager.
     * @param keys Lua table with key mappings.
     * @param controllerManager Unique pointer to ControllerManager instance.
     */
  void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& 
  controllerManager);

   /**
     * @brief Loads button bindings from Lua table into the ControllerManager.
     * @param buttons Lua table with button mappings.
     * @param controllerManager Unique pointer to ControllerManager instance.
     */
  void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& 
  controllerManager);

    /**
     * @brief Loads entities from Lua table into the ECS Registry.
     * @param lua Reference to Lua state.
     * @param entities Lua table containing entity definitions.
     * @param registry Unique pointer to ECS Registry.
     */  
  void LoadEntities(sol::state& lua, const sol::table& entites, 
  std::unique_ptr<Registry>& registry);

   /**
     * @brief Loads music assets from Lua table into the AssetManager.
     * @param musicTable Lua table containing music definitions.
     * @param assetManager Unique pointer to the AssetManager instance.
     */
  void LoadMusic(const sol::table& musicTable, std::unique_ptr<AssetManager>& assetManager);

  public:
  SceneLoader();
  ~SceneLoader();

   /**
     * @brief Loads a full scene from a Lua file path, setting up assets, controls, entities, and music.
     * @param scenePath File path to the Lua scene script.
     * @param lua Reference to the Lua scripting state.
     * @param assetManager Unique pointer to AssetManager.
     * @param controllerManager Unique pointer to ControllerManager.
     * @param registry Unique pointer to ECS Registry.
     * @param renderer SDL renderer pointer for texture creation.
     */
  void LoadScene(const std::string& scenePath, sol::state& lua
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};

#endif