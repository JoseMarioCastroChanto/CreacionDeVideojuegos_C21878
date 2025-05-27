#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

/**
 * @class AssetManager
 * @brief Manages textures, fonts, and music assets using SDL2.
 *
 * This class handles loading, storing, retrieving, and clearing of 
 * SDL_Texture, TTF_Font, and Mix_Music assets. It centralizes asset 
 * management to avoid redundant loads and ensures proper cleanup.
 */
class AssetManager {
 private:
  /// Map of texture IDs to SDL_Texture pointers.
  std::map<std::string, SDL_Texture*> textures;

  /// Map of font IDs to TTF_Font pointers.
  std::map<std::string, TTF_Font*> fonts;

  /// Map of music IDs to Mix_Music pointers.
  std::map<std::string, Mix_Music*> musics;

  /// Currently playing music.
  Mix_Music* currentMusic = nullptr;

 public:
  /**
   * @brief Constructs a new AssetManager instance.
   */
  AssetManager();

  /**
   * @brief Destroys the AssetManager and releases all loaded assets.
   */
  ~AssetManager();

  /**
   * @brief Frees all textures, fonts, and music.
   */
  void ClearAssets();

  /**
   * @brief Loads and stores a texture from file.
   * 
   * @param renderer The SDL_Renderer used to create the texture.
   * @param textureId The unique ID to associate with the texture.
   * @param filePath The path to the texture file.
   */
  void AddTexture(SDL_Renderer* renderer, const std::string& textureId,
                  const std::string& filePath);

  /**
   * @brief Retrieves a previously loaded texture.
   * 
   * @param textureId The ID of the texture to retrieve.
   * @return SDL_Texture* Pointer to the texture, or nullptr if not found.
   */
  SDL_Texture* GetTexture(const std::string& textureId);

  /**
   * @brief Loads and stores a font from file.
   * 
   * @param fontId The unique ID to associate with the font.
   * @param filePath The path to the font file.
   * @param fontSize The font size to use.
   */
  void AddFont(const std::string& fontId, const std::string& filePath, int fontSize);

  /**
   * @brief Retrieves a previously loaded font.
   * 
   * @param fontId The ID of the font to retrieve.
   * @return TTF_Font* Pointer to the font, or nullptr if not found.
   */
  TTF_Font* GetFont(const std::string& fontId);

  /**
   * @brief Loads a music track from file.
   * 
   * @param musicId The unique ID to associate with the music.
   * @param filePath The path to the music file.
   */
  void LoadMusic(const std::string& musicId, const std::string& filePath);

  /**
   * @brief Plays a loaded music track.
   * 
   * @param musicId The ID of the music to play.
   * @param loops Number of times the music should loop. Default is -1 (infinite).
   */
  void PlayMusic(const std::string& musicId, int loops = -1);

  /**
   * @brief Stops the currently playing music.
   */
  void StopMusic();

  /**
   * @brief Resumes paused music playback.
   */
  void ResumeMusic();

  /**
   * @brief Pauses the currently playing music.
   */
  void PauseMusic();

  /**
   * @brief Frees all loaded music assets.
   */
  void ClearMusic();
};

#endif // ASSETMANAGER_HPP
