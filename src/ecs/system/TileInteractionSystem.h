/*
 *  TileInteractionSystem.h
 *  Handles collisions between player and tiles.
 */

#ifndef MAZIAC_TILEINTERACTIONSYSTEM_H
#define MAZIAC_TILEINTERACTIONSYSTEM_H
#include "event/BaseEvent.h"

class World;

class TileInteractionSystem {
public:
    TileInteractionSystem(World &world);
    void update(float deltaTime);
private:
    float currentWait = 0.5f; // limits how often you can interact with a tile
    float maxWait = 0.5f;

    bool getCollisionEntities(const CollisionEvent &e, Entity *&player, Entity *&other);

    void onEnergyCollision(Entity* tile, World& world);
    void onWeaponCollision(Entity* player, Entity* tile, World& world);
    void onTreasureCollision(Entity* player, Entity* tile, World& world);
};

#endif //MAZIAC_TILEINTERACTIONSYSTEM_H