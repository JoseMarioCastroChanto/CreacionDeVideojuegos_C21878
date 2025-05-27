#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <memory>
#include <sol/sol.hpp>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"

const int FPS = 30;  ///< Frames per second target.
const int MILISECS_PER_FRAME = 1000 / FPS;///< Milliseconds per frame.

/**
 * @brief Core class that manages the entire game lifecycle.
 * 
 * This class handles initialization, the main game loop, input processing,
 * scene management, updates, rendering, and resource cleanup. It follows
 * the singleton pattern to ensure a single instance throughout the game.
 */
class Game {
private:
    SDL_Window* window = nullptr;  ///< The SDL window.
    

    int windowWidth = 0;///< Window width in pixels.
    int windowHeight = 0; ///< Window height in pixels.

    int milisecsPreviousFrame = 0;///< Timestamp of previous frame in milliseconds.

    bool isRunning = false;///< Flag to check if game loop is running.
    bool isPaused = false;///< Flag to check if the game is currently paused.
    bool wasPaused = false;///< Flag to check if the game was paused in the last frame.


public:
    SDL_Renderer* renderer = nullptr;///< SDL renderer pointer.
    std::unique_ptr<AssetManager> assetManager; ///< Manages game assets.
    std::unique_ptr<EventManager> eventManager;///< Manages events and event listeners.
    std::unique_ptr<ControllerManager> controllerManager;///< Manages input controllers.
    std::unique_ptr<Registry> registry;///< ECS registry for entities and components.
    std::unique_ptr<SceneManager> sceneManager;///< Manages game scenes.
    sol::state lua;///< Lua scripting state.

private:
    void Setup();///< Setup initial game state and resources.
    void RunScene();///< Execute the current scene's logic.
    void ProcessInput();///< Handle input processing.
    void Update();///< Update game logic.
    void Render(); ///< Render the current frame.

     Game();///< Private constructor for singleton pattern.
    ~Game();///< Destructor.

public: 
    /**
     * @brief Provides global access to the single Game instance.
     * @return Reference to the Game instance.
     */
    static Game& GetInstance();
     /**
     * @brief Initializes the game (window, subsystems, resources).
     */
    void Init();
     /**
     * @brief Runs the main game loop.
     */
    void Run();
    /**
     * @brief Cleans up and destroys all game resources.
     */
    void Destroy();
};
#endif