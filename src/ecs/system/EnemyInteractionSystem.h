/*
 *  EnemyInteractionSystem.h
 *  Declares the methods for player/enemy interactions.
 */

#ifndef MAZIAC_EVENTRESPONSESYSTEM_H
#define MAZIAC_EVENTRESPONSESYSTEM_H

#include "Component.h"
#include "event/BaseEvent.h"

// forward declare
class Entity;
class World;

class EnemyInteractionSystem {
public:
    EnemyInteractionSystem(World &world);
private:
    void onEnemyCollision(const CollisionEvent& e, World& world);
    void playFightAnimationSequence(Entity* player, bool hasWeapon, EnergyState* energyState);
};

#endif //MAZIAC_EVENTRESPONSESYSTEM_H