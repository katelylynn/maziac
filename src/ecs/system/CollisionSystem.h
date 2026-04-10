/*
 *  CollisionSystem.h
 *  Defines a set of active collisions and helper functions to query and make keys for collidables.
 */

#ifndef MAZIAC_COLLISIONSYSTEM_H
#define MAZIAC_COLLISIONSYSTEM_H

#include <algorithm>
#include <memory>
#include <set>
#include <vector>
#include "Entity.h"

// type alias
using CollisionKey = std::pair<Entity*, Entity*>;

// forward declaration to remove circular dependencies
class World;

class CollisionSystem {
public:
    void update(World& world);
    std::set<CollisionKey> activeCollisions;
private:
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);
    CollisionKey makeKey(Entity* entityA, Entity* entityB) {
        // minmax automatically orders our pair so smaller number (memory address) is ordered first
        // (Enemy, Player)
        // (Player, Enemy) -> (Enemy, Player)
        return std::minmax(entityA, entityB);
    }
};

#endif //MAZIAC_COLLISIONSYSTEM_H