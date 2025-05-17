#ifndef SCENETIMESYSTEM_HPP
#define SCENETIMESYSTEM_HPP

#include <SDL2/SDL.h>

class SceneTimeSystem  : public System{
private:
    int sceneStartTime;
    int currentTime;
    int deltaTime;

public:
    SceneTimeSystem() {
        sceneStartTime = SDL_GetTicks();
        currentTime = 0;
        deltaTime = 0;
    }

    void Update() {
        int now = SDL_GetTicks();
        deltaTime = now - currentTime;
        currentTime = now;
    }

    int GetSceneTime() const {
        return currentTime - sceneStartTime;
    }

    int GetDeltaTime() const {
        return deltaTime;
    }

    void Reset() {
        sceneStartTime = SDL_GetTicks();
        currentTime = sceneStartTime;
        deltaTime = 0;
    }
};

#endif