//
// Created by kate on 2026-02-25.
//

#ifndef COMP8051_CAMERASYSTEM_H
#define COMP8051_CAMERASYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class CameraSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        // find the player
        for (auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>()) {
                playerEntity = entity.get();
                break;
            }
        }

        if (!playerEntity) return;

        auto& playerTransform = playerEntity->getComponent<Transform>();
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                auto& camera = entity->getComponent<Camera>();

                // position the camera so the player is in the center of its view
                camera.view.x = playerTransform.position.x - camera.view.w / 2;
                camera.view.y = playerTransform.position.y - camera.view.h / 2;

                // clamp the camera so it stays within the world window
                if (camera.view.x < 0) camera.view.x = 0;
                if (camera.view.y < 0) camera.view.y = 0;
                if (camera.view.x > camera.worldWidth - camera.view.w)
                    camera.view.x = camera.worldWidth - camera.view.w;
                if (camera.view.y > camera.worldHeight - camera.view.h)
                    camera.view.y = camera.worldHeight - camera.view.h;
            }
        }
    }
};

#endif //COMP8051_CAMERASYSTEM_H