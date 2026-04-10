/*
 *  MovementSystem.h
 *  Updates an entity's position if it has a transform, translation and velocity component.
 */

#ifndef MAZIAC_MOVEMENTSYSTEM_H
#define MAZIAC_MOVEMENTSYSTEM_H
#include <memory>

#include "Component.h"

class World;

class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float deltaTime, World* world);
};

#endif //MAZIAC_MOVEMENTSYSTEM_H