#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <tuple>

/**
 * @class ControllerManager
 * @brief Handles keyboard and mouse input mapping and state tracking.
 */
class ControllerManager {
 private:
  /// Maps action names to keyboard key codes.
  std::map<std::string, int> actionKeyName;
  
  /// Tracks key pressed states by key code.
  std::map<int, bool> keyDown;

  /// Maps mouse button names to button codes.
  std::map<std::string, int> mouseButtonName;
  
  /// Tracks mouse button pressed states by button code.
  std::map<int, bool> mouseButtonDown;

  /// Current mouse X position.
  int mousePosX;
  
  /// Current mouse Y position.
  int mousePosY;

 public:
  /**
   * @brief Constructor that initializes the controller manager.
   */
  ControllerManager();
  
  /**
   * @brief Destructor.
   */
  ~ControllerManager();

  /**
   * @brief Clears all stored key and action mappings.
   */
  void Clear();

  // Keyboard input methods

  /**
   * @brief Maps an action name to a keyboard key code.
   * @param action The name of the action (e.g., "Jump").
   * @param keyCode The SDL key code to bind to the action.
   */
  void AddActionKey(const std::string& action, int keyCode);
  
  /**
   * @brief Marks the specified key code as pressed.
   * @param keyCode The SDL key code pressed.
   */
  void KeyDown(int keyCode);
  
  /**
   * @brief Marks the specified key code as released.
   * @param keyCode The SDL key code released.
   */
  void KeyUp(int keyCode);
  
  /**
   * @brief Checks if the specified action is currently active (key pressed).
   * @param action The name of the action.
   * @return True if the key bound to the action is pressed; otherwise false.
   */
  bool IsActionActivated(const std::string& action);

  // Mouse input methods

  /**
   * @brief Maps a mouse button name to a mouse button code.
   * @param name The name of the mouse button (e.g., "LeftClick").
   * @param buttonCode The SDL mouse button code.
   */
  void AddMouseButton(const std::string& name, int buttonCode);
  
  /**
   * @brief Marks the specified mouse button code as pressed.
   * @param buttonCode The mouse button code pressed.
   */
  void MouseButtonDown(int buttonCode);
  
  /**
   * @brief Marks the specified mouse button code as released.
   * @param buttonCode The mouse button code released.
   */
  void MouseButtonUp(int buttonCode);
  
  /**
   * @brief Checks if the specified mouse button is currently pressed.
   * @param name The name of the mouse button.
   * @return True if the mouse button is pressed; otherwise false.
   */
  bool IsMouseButtonDown(const std::string& name);

  /**
   * @brief Sets the current mouse position.
   * @param x The x-coordinate of the mouse.
   * @param y The y-coordinate of the mouse.
   */
  void SetMousePosition(int x, int y);
  
  /**
   * @brief Gets the current mouse position.
   * @return A tuple with the x and y coordinates of the mouse.
   */
  std::tuple<int, int> GetMousePosition();
};

#endif
