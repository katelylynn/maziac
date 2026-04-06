/*
 *  EventResponseSystem.h
 *  Declares the methods for collision and mouse interaction events.
 */

#ifndef MAZIAC_EVENTRESPONSESYSTEM_H
#define MAZIAC_EVENTRESPONSESYSTEM_H

#include "event/BaseEvent.h"

// forward declare
class Entity;
class World;

class EventResponseSystem {
public:
    EventResponseSystem(World &world);
private:
    // collisions
    void onCollision(const CollisionEvent& e, const char* otherTag, World& world, bool* resolved);
    bool getCollisionEntities(const CollisionEvent& e, const char* otherTag, Entity*&, Entity*& other);

    // mouse interactions
    void onMouseInteraction(const MouseInteractionEvent& e);
};

#endif //MAZIAC_EVENTRESPONSESYSTEM_H