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
        EnergyState* energyState = nullptr;

        // find scene state entity
        for (auto& e : entities) {
            if (e->hasComponent<EnergyState>()) {
                energyState = &e.get()->getComponent<EnergyState>();
                break;
            }
        }

        if (!energyState) return;

        energyState->energy -= deltaTime * energyState->energyDepletionRate;

        if (energyState->energy < 0.0f) {
            Game::onSceneChangeRequest("lose");
        }
    }
}
