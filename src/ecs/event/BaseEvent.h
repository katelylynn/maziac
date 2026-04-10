/*
 *  BaseEvent.h
 *  Defines base event and its children event types.
 */

#ifndef MAZIAC_BASEEVENT_H
#define MAZIAC_BASEEVENT_H
#include "Entity.h"

enum class EventType {
    Collision,
    PlayerAction,
};

struct BaseEvent {
    EventType type{};
    // "virtual" hint on a base deconstructor ensures object is destroyed properly
    virtual ~BaseEvent() = default;
};

enum class CollisionState { Enter, Stay, Exit };

struct CollisionEvent : BaseEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
    CollisionState state{};

    CollisionEvent(Entity* entityA, Entity* entityB, CollisionState state) : entityA(entityA), entityB(entityB), state(state) {
        type = EventType::Collision;
    }
};

#endif //MAZIAC_BASEEVENT_H