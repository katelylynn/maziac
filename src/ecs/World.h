/*
 *  World.h
 *  Stores entity, map and event manager references, and updates systems.
 */

#ifndef MAZIAC_WORLD_H
#define MAZIAC_WORLD_H
#include <memory>
#include <vector>

#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "EnergyDepletionSystem.h"
#include "Entity.h"
#include "EventResponseSystem.h"
#include "event/EventManager.h"
#include "KeyboardInputSystem.h"
#include "MainMenuSystem.h"
#include "Map.h"
#include "MouseInputSystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "UIRenderSystem.h"
#include "scene/SceneType.h"

class World {
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;

    // systems
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    EventManager eventManager;
    EventResponseSystem eventResponseSystem{*this};
    MainMenuSystem mainMenuSystem;
    UIRenderSystem uiRenderSystem;
    MouseInputSystem mouseInputSystem;
    EnergyDepletionSystem energyDepletionSystem;
public:
    World() = default;

    void update(
        float deltaTime, const SDL_Event& event, SceneType sceneType
    ) {
        if (sceneType == SceneType::MainMenu) {
            mainMenuSystem.update(event);
        } else {
            keyboardInputSystem.update(entities, event);
            movementSystem.update(entities, deltaTime, this);
            collisionSystem.update(*this);
            animationSystem.update(entities, deltaTime);
            energyDepletionSystem.update(entities, deltaTime);
        }

        mouseInputSystem.update(*this, event);

        synchronizeEntities();
        cleanup();
    }

    void render() {
        map.draw();
        renderSystem.render(entities);
        uiRenderSystem.render(entities);
    }

    Entity& createEntity() {
        // emplace_back: inserts a new element at the end of a vector
        // emplace instead of push so we don't create a copy
        // make_unique: creates a unique_ptr object
        entities.emplace_back(std::make_unique<Entity>());

        // return dereferenced version of the last entity
        return *entities.back();
    }

    Entity& createDeferredEntity() {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanup() {
        // use a lambda predicate to remove all inactive entities
        std::erase_if(entities, [](std::unique_ptr<Entity>& entity) {
           return !entity->isActive();
        });
    }

    void synchronizeEntities() {
        if (!deferredEntities.empty()) {
            // push back all deferred entities to the entities vector
            // using move so we don't create a copy
            std::move(
                deferredEntities.begin(),
                deferredEntities.end(),
                std::back_inserter(entities)
            );
            // clearing the creation buffer
            deferredEntities.clear();
        }
    }

    EventManager& getEventManager() { return eventManager; }

    Map& getMap() { return map; }
};

#endif //MAZIAC_WORLD_H