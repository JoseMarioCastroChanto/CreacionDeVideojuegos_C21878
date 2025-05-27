#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "SceneLoader.hpp"


/**
 * @brief Manages scenes and handles scene transitions.
 */
class SceneManager{
 private:
  std::map<std::string, std::string> scenes;/// Map of scene names to script paths
  std::string nextScene;/// Name of the next scene to load
  bool isSceneRunning = false;/// Flag indicating if a scene is currently running
  std::unique_ptr<SceneLoader> sceneLoader;///Pointer to the SceneLoader used for loading scenes.

public:
    /**
     * @brief Constructs the SceneManager.
     */
 SceneManager();
     /**
     * @brief Destructs the SceneManager.
     */
 ~SceneManager();

    /**
     * @brief Loads a scene from a Lua script file.
     * @param path The path to the Lua script.
     * @param lua The Lua state.
     */
 void LoadSceneFromScript(const std::string& path, sol::state& lua);
     /**
     * @brief Loads the next scene based on internal state.
     */
 void LoadScene();

    /**
     * @brief Returns the name of the next scene to be loaded.
     * @return The next scene's name.
     */
 std::string GetNextScene() const;

     /**
     * @brief Sets the name of the next scene to be loaded.
     * @param nextScene The next scene's name.
     */
 void SetNextScene(const std::string& nextScene);
    /**
     * @brief Checks whether a scene is currently running.
     * @return True if a scene is running, false otherwise.
     */
 bool IsSceneRunning() const;
     /**
     * @brief Marks the beginning of a scene's execution.
     */
 void StartScene();

    /**
     * @brief Stops the currently running scene.
     */
 void StopScene();
};
#endif