//
// Created by kate on 2026-03-11.
//

#ifndef COMP8051_BASEEVENT_H
#define COMP8051_BASEEVENT_H
#include "Entity.h"

enum class EventType {
    Collision,
    PlayerAction,
    MouseInteraction,
};

struct BaseEvent {
    EventType type{};
    // in c++ always make the destructor virtual from a class you are deriving from
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

enum class PlayerAction { Attack, Interact, useItem, Jump };

struct PlayerActionEvent : BaseEvent {
    Entity* player = nullptr;
    PlayerAction action{};

    PlayerActionEvent(Entity* player, PlayerAction action) : player(player), action(action) {
        type = EventType::PlayerAction;
    }
};

enum class MouseInteractionState { Pressed, Released, Cancel };

struct MouseInteractionEvent : BaseEvent {
    Entity* entity = nullptr; // the entity we interacted with our mouse
    MouseInteractionState state{};

    MouseInteractionEvent(Entity* entity, MouseInteractionState state) : entity(entity), state(state) {
        type = EventType::MouseInteraction;
    }
};

#endif //COMP8051_BASEEVENT_H