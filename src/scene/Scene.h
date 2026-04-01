/*
 *  Scene.h
 *  Defines the methods needed for a scene.
 */

#ifndef MAZIAC_SCENE_H
#define MAZIAC_SCENE_H

#include "World.h"
#include "SceneType.h"

class Scene {
public:
    Scene(SceneType sceneType, const char* sceneName, const char* mapPath, int windowWidth, int windowHeight);

    void update(const float deltaTime, const SDL_Event &e) {
        world.update(deltaTime, e, type);
    }

    void render() {
        world.render();
    }

    World world;

    const std::string& getName() const { return name; }
private:
    std::string name;
    SceneType type;

    void initMainMenu(int windowWidth, int windowHeight);
    void initGameplay(const char* mapPath, int windowWidth, int windowHeight);
};

#endif //MAZIAC_SCENE_H