/*
 *  EnergyDepletionSystem.cpp
 *  Handles energy depletion and calling game over.
 */

#include "EnergyDepletionSystem.h"

#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "Game.h"

void EnergyDepletionSystem::update(const std::vector<std::unique_ptr<Entity> > &entities, float deltaTime) {
    {
        SceneState* sceneState = nullptr;

        // find scene state entity
        for (auto& e : entities) {
            if (e->hasComponent<SceneState>()) {
                sceneState = &e.get()->getComponent<SceneState>();
                break;
            }
        }

        if (!sceneState) return;

        sceneState->energy -= deltaTime * sceneState->energyDepletionRate;
        std::cout << sceneState->energy << std::endl;

        if (sceneState->energy < 0.0f) {
            Game::onSceneChangeRequest("lose");
        }
    }
}
