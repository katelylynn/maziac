//
// Created by kate on 2026-02-25.
//

#include "../scene/Scene.h"

#include "Game.h"
#include "manager/AssetManager.h"

Scene::Scene(SceneType sceneType, const char *sceneName, const char *mapPath, int windowWidth, int windowHeight)
: name(sceneName), type(sceneType) {
    if (sceneType == SceneType::MainMenu)
        initMainMenu(windowWidth, windowHeight);
    else
        initGameplay(mapPath, windowWidth, windowHeight);
}

void Scene::initMainMenu(int windowWidth, int windowHeight) {
    //
}

void Scene::initGameplay(const char* mapPath, int windowWidth, int windowHeight) {
    // MAP
    world.getMap().load(mapPath, TextureManager::load("../asset/map/map_tileset.png"));

    // CAMERA
    auto& camera = world.createEntity();
    SDL_FRect cameraView{};
    cameraView.w = windowWidth;
    cameraView.h = windowHeight;
    camera.addComponent<Camera>(
        cameraView,
        // set the size of the whole world
        world.getMap().mapWidth * (float) world.getMap().tileHeight,
        world.getMap().mapHeight * (float) world.getMap().tileHeight
    );

    // PLAYER
    auto& player(world.createEntity());
    player.addComponent<PlayerTag>();

    auto& playerTransform = player.addComponent<Transform>(Vector2D(16, 16), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0, 0), 10.0f);

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture* playerTexture = TextureManager::load("../asset/animations/diver_anim.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
    SDL_FRect playerDest { playerTransform.position.x, playerTransform.position.y, 16, 16 };
    player.addComponent<Sprite>(playerTexture, playerSrc, playerDest);
}
