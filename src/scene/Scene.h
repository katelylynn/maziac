/*
 *  Scene.h
 *  Defines the methods needed for a scene.
 */

#ifndef MAZIAC_SCENE_H
#define MAZIAC_SCENE_H

#include "World.h"

class Scene {
public:
    Scene(const char* sceneName, const char* mapPath);

    void update(const float deltaTime, const SDL_Event &e) {
        world.update(deltaTime, e);
    }

    void render() {
        world.render();
    }

    World world;

    const std::string& getName() const { return name; }
private:
    std::string name;

    void initGameplay(const char* mapPath);
};

#endif //MAZIAC_SCENE_H