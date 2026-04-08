/*
 *  EventResponseSystem.h
 *  Declares the methods for collision and mouse interaction events.
 */

#ifndef MAZIAC_EVENTRESPONSESYSTEM_H
#define MAZIAC_EVENTRESPONSESYSTEM_H

#include "Component.h"
#include "event/BaseEvent.h"

// forward declare
class Entity;
class World;

class EventResponseSystem {
public:
    EventResponseSystem(World &world);
private:
    // enemy interactions
    void onEnemyCollision(const CollisionEvent& e, World& world);
    void playFightAnimationSequence(Entity* player, bool hasWeapon, EnergyState* energyState);

    // mouse interactions
    void onMouseInteraction(const MouseInteractionEvent& e);
};

#endif //MAZIAC_EVENTRESPONSESYSTEM_H