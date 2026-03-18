//
// Created by kate on 2026-03-11.
//

#ifndef COMP8051_EVENTRESPONSESYSTEM_H
#define COMP8051_EVENTRESPONSESYSTEM_H
#include <functional>

#include "event/BaseEvent.h"

// forward declare
class Entity;
class World;

class EventResponseSystem {
public:
    EventResponseSystem(World &world);
private:
    // collisions
    void onCollision(const CollisionEvent& e, const char* otherTag, World& world);
    bool getCollisionEntities(const CollisionEvent& e, const char* otherTag, Entity*&, Entity*& other);

    // player action
    void onPlayerAction(
        const PlayerActionEvent& e,
        const std::function<void(Entity* player, PlayerAction action)>& callback
    );

    // mouse interactions
    void onMouseInteraction(const MouseInteractionEvent& e);
};

#endif //COMP8051_EVENTRESPONSESYSTEM_H