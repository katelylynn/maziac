//
// Created by kate on 2026-02-25.
//

#ifndef COMP8051_SCENEMANAGER_H
#define COMP8051_SCENEMANAGER_H
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "../scene/Scene.h"

struct SceneParameters {
    SceneType sceneType;
    const char *name;
    const char *mapPath;
    int windowWidth;
    int windowHeight;
};

class SceneManager {
    std::unordered_map<std::string, SceneParameters> sceneParameters;

    std::string pendingScene;

    void changeScene(const std::string &name) {
        auto it = sceneParameters.find(name);
        if (it != sceneParameters.end()) {
            const auto& params = it->second;
            // create Scene object
            currentScene = std::make_unique<Scene>(
                params.sceneType,
                params.name,
                params.mapPath,
                params.windowWidth,
                params.windowHeight
            );
        } else {
            std::cerr << "Scene" << name << " does not exist" << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;

    void loadScene(SceneType sceneType, const char* sceneName, const char* mapPath, int windowWidth, int windowHeight) {
         sceneParameters[sceneName] = { sceneType, sceneName, mapPath, windowWidth, windowHeight };
    }

    // defer scene until end of game loop so that Game can finish its functionality
    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(const float deltaTime, const SDL_Event &e) {
        if (currentScene) currentScene->update(deltaTime, e); // all of our world updates
        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const {
        if (currentScene) currentScene->render();
    }
};

#endif //COMP8051_SCENEMANAGER_H