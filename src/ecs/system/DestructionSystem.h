//
// Created by kate on 2026-02-25.
//

#ifndef COMP8051_DESTRUCTIONSYSTEM_H
#define COMP8051_DESTRUCTIONSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

// destroys any entities that go outside camera view
class DestructionSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* cameraEntity = nullptr;

        // find camera
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }

        if (!cameraEntity) return;
        auto& camera = cameraEntity->getComponent<Camera>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<ProjectileTag>()) {
                auto& transform = entity->getComponent<Transform>();

                // destroy entity if it goes out the camera view
                if (
                    transform.position.x > camera.view.x + camera.view.w ||
                    transform.position.x < camera.view.x ||
                    transform.position.y > camera.view.y + camera.view.h ||
                    transform.position.y < camera.view.y
                )
                    entity->destroy();
            }
        }
    }
};

#endif //COMP8051_DESTRUCTIONSYSTEM_H