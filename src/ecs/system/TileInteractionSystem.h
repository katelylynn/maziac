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
private:
    void onCollision(const CollisionEvent& e, const char *otherTag, World& world);
    bool getCollisionEntities(const CollisionEvent &e, const char *otherTag, Entity *&player, Entity *&other);
};

#endif //MAZIAC_TILEINTERACTIONSYSTEM_H