/*
 *  EventResponseSystem.cpp
 *  Handles the response for different types of events.
 */

#include "EventResponseSystem.h"

#include "Game.h"
#include "World.h"

EventResponseSystem::EventResponseSystem(World &world) {
    // collision subscription
    world.getEventManager().subscribe(
        [this, &world](const BaseEvent& e) {
            if (e.type != EventType::Collision) return;

            // cast base type to collision type
            const auto& collision = static_cast<const CollisionEvent&>(e);

            onCollision(collision, "wall", world);
        }
    );

    // mouse interaction subscription
    world.getEventManager().subscribe(
        [this, &world](const BaseEvent& e) {
            if (e.type != EventType::MouseInteraction) return;

            const auto& mouseInteractionEvent = static_cast<const MouseInteractionEvent&>(e);

            onMouseInteraction(mouseInteractionEvent);
        }
    );
}

void EventResponseSystem::onCollision(
    const CollisionEvent& e,
    const char *otherTag,
    World& world
) {
    Entity* player = nullptr;
    Entity* other = nullptr;

    if (!getCollisionEntities(e, otherTag, player, other)) return;

    if (std::string(otherTag) == "wall") {
        // stay bc need to constantly check if player colliding w wall
        if (e.state != CollisionState::Stay) return;
        auto& transform = player->getComponent<Transform>();
        auto& translation = player->getComponent<Translation>();

        // reset
        transform.position = translation.endPosition = translation.startPosition;
    }
}

bool EventResponseSystem::getCollisionEntities(
    const CollisionEvent &e,
    const char *otherTag,
    Entity *&player,
    Entity *&other
) {

    // check both entities exist
    if (e.entityA == nullptr || e.entityB == nullptr)
        return false;

    // check both entities have colliders
    if (!(e.entityA->hasComponent<Collider>() && e.entityB->hasComponent<Collider>()))
        return false;

    auto& colliderA = e.entityA->getComponent<Collider>();
    auto& colliderB = e.entityB->getComponent<Collider>();

    if (colliderA.tag == "player" && colliderB.tag == otherTag) {
        player = e.entityA;
        other = e.entityB;
    }
    else if (colliderA.tag == otherTag && colliderB.tag == "player") {
        player = e.entityB;
        other = e.entityA;
    }

    return player && other;
}

void EventResponseSystem::onMouseInteraction(const MouseInteractionEvent &e) {
    if (!e.entity->hasComponent<Clickable>()) return;

    auto& clickable = e.entity->getComponent<Clickable>();

    switch (e.state) {
        case MouseInteractionState::Pressed:
            clickable.onPressed();
            break;
        case MouseInteractionState::Released:
            clickable.onReleased();
            break;
        case MouseInteractionState::Cancel:
            clickable.onCancel();
            break;
        default:
            break;
    }
}
