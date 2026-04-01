/*
 *  EnergyDepletionSystem.h
 *  Defines the methods to deplete energy over time.
 */

#ifndef MAZIAC_ENERGYDEPLETIONSYSTEM_H
#define MAZIAC_ENERGYDEPLETIONSYSTEM_H
#include <memory>
#include <vector>

#include "Entity.h"

class EnergyDepletionSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);
};

#endif //MAZIAC_ENERGYDEPLETIONSYSTEM_H