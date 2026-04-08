/*
 *  Scene.cpp
 *  Creates entities and assigns their components.
 */

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
    Map& map = world.getMap();
    map.load(mapPath, TextureManager::load("asset/map/map_tileset.png"));

    // SCENE STATE
    auto &sceneState(world.createEntity());
    sceneState.addComponent<SceneState>();

    // ENERGY STATE
    auto &energyState(world.createEntity());
    energyState.addComponent<EnergyState>();
    energyState.getComponent<EnergyState>().energyDepletionRate = energyState.getComponent<EnergyState>().initialEnergyDepletionRate;

    // ITEM COLLIDERS
    for (int row = 0; row < map.mapHeight; row++) {
        for (int col = 0; col < map.mapWidth; col++) {
            // world layers
            for (auto layerPair : map.layers) {
                if ((*layerPair.second)[row][col] != 0) {
                    auto& tile = world.createEntity();
                    tile.addComponent<Transform>(Vector2D(map.tileWidth * col, map.tileHeight * row), 0.0f, 1.0f);

                    Collider& c = tile.addComponent<Collider>(layerPair.first);
                    c.rect.x = map.tileWidth * col;
                    c.rect.y = map.tileHeight * row;
                    c.rect.w = map.tileWidth;
                    c.rect.h = map.tileHeight;

                    break;
                }
            }
        }
    }

    // ENERGY BAR
    auto& energyBar(world.createEntity());
    energyBar.addComponent<Observer<float>>(
        &energyState.getComponent<EnergyState>().energy, 0.0f, [&energyState, &map]() {
            float increments = energyState.getComponent<EnergyState>().initialEnergy / map.energyBar.size();
            int energyLevel = static_cast<int>(energyState.getComponent<EnergyState>().energy / increments);

            for (int tile = 0; tile < map.energyBar.size(); tile++) {
                if (tile + 1 >= map.energyBar.size() - energyLevel) map.energyBar[tile] = true;
                else if (tile + 1 < map.energyBar.size() - energyLevel) map.energyBar[tile] = false;
            }
        }
    );

    // load character anim
    Animation animation = AssetManager::getAnimation("character");
    animation.repeating = true;

    // PLAYER
    auto& player(world.createEntity());
    player.addComponent<Player>(Item::None);

    auto& playerTransform = player.addComponent<Transform>(map.playerSpawnpoint.position, 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0, 0), 20.0f);
    player.addComponent<Translation>();

    player.addComponent<Animation>(animation);

    SDL_Texture* playerTexture = TextureManager::load("asset/animations/diver_anim.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
    SDL_FRect playerDest { playerTransform.position.x, playerTransform.position.y, 16, 16 };
    player.addComponent<Sprite>(playerTexture, playerSrc, playerDest);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDest.w * 0.99f;
    playerCollider.rect.h = playerDest.h * 0.99f;
    playerCollider.rect.x = playerDest.x;
    playerCollider.offset.x = (playerDest.w - playerCollider.rect.w) / 2.0f;
    playerCollider.offset.y = (playerDest.h - playerCollider.rect.h) / 2.0f;

    // ENEMIES
    for (Spawnpoint sp : map.enemySpawnpoints) {
        auto& enemy(world.createEntity());
        auto& enemyComponent = enemy.addComponent<Enemy>();
        enemyComponent.startingPosition = sp.position;

        auto& enemyTransform = enemy.addComponent<Transform>(sp.position, 0.0f, 1.0f);
        enemy.addComponent<Velocity>(Vector2D(0, 0), 20.0f);
        enemy.addComponent<Translation>();

        enemy.addComponent<Animation>(animation);

        SDL_Texture* enemyTexture = TextureManager::load("asset/animations/enemy_anim.png");
        SDL_FRect enemySrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
        SDL_FRect enemyDest { enemyTransform.position.x, enemyTransform.position.y, 16, 16 };
        enemy.addComponent<Sprite>(enemyTexture, enemySrc, enemyDest);

        auto& enemyCollider = enemy.addComponent<Collider>("enemy");
        enemyCollider.rect.w = enemyDest.w * 0.99f;
        enemyCollider.rect.h = enemyDest.h * 0.99f;
        enemyCollider.rect.x = enemyDest.x;
        enemyCollider.offset.x = (enemyDest.w - enemyCollider.rect.w) / 2.0f;
        enemyCollider.offset.y = (enemyDest.h - enemyCollider.rect.h) / 2.0f;
    }
}
