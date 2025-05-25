#ifndef SCENETIMESYSTEM_HPP
#define SCENETIMESYSTEM_HPP

#include <SDL2/SDL.h>
#include <iostream>

class SceneTimeSystem : public System {
private:
    int sceneStartTime;
    int currentTime;
    int deltaTime;
    bool paused;
    int pauseStartTime; 
    int totalPausedTime; 
public:
    SceneTimeSystem() {
        sceneStartTime = SDL_GetTicks();
        currentTime = sceneStartTime;
        deltaTime = 0;
        paused = false;
        pauseStartTime = 0;
        totalPausedTime = 0;
    }

    void Pause() {
        if (!paused) {
            paused = true;
            pauseStartTime = SDL_GetTicks();
        }
    }

    void Resume() {
        if (paused) {
            paused = false;
            int pauseDuration = SDL_GetTicks() - pauseStartTime;
            totalPausedTime += pauseDuration;
            currentTime = SDL_GetTicks();
        }
    }

    void Update() {
        if (paused) {
            deltaTime = 0;
            return;
        }

        int now = SDL_GetTicks();
        deltaTime = now - currentTime;
        currentTime = now;
    }

    int GetSceneTime() const {
        return (currentTime - sceneStartTime - totalPausedTime);
    }

    int GetDeltaTime() const {
        return deltaTime;
    }

    void Reset() {
        sceneStartTime = SDL_GetTicks();
        currentTime = sceneStartTime;
        deltaTime = 0;
        paused = false;
        pauseStartTime = 0;
        totalPausedTime = 0;
    }
};

#endif
