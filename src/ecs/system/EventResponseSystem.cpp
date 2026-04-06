/*
 *  EventResponseSystem.cpp
 *  Handles the response for different types of events.
 */

#include "EventResponseSystem.h"

#include "Game.h"
#include "manager/AssetManager.h"

EventResponseSystem::EventResponseSystem(World &world) {
    // collision subscription
    world.getEventManager().subscribe(
        [this](const BaseEvent& e) {
            if (e.type != EventType::Collision) return;

            // cast base type to collision type
            onEnemyCollision(static_cast<const CollisionEvent&>(e));
        }
    );

    // mouse interaction subscription
    world.getEventManager().subscribe(
        [this](const BaseEvent& e) {
            if (e.type != EventType::MouseInteraction) return;

            const auto& mouseInteractionEvent = static_cast<const MouseInteractionEvent&>(e);

            onMouseInteraction(mouseInteractionEvent);
        }
    );
}

void EventResponseSystem::onEnemyCollision(const CollisionEvent& e) {
    if (e.state != CollisionState::Enter) return;

    Entity* player = nullptr;
    Entity* enemy = nullptr;

    // check both entities exist
    if (e.entityA == nullptr || e.entityB == nullptr) return;

    // check both entities have colliders
    if (!(e.entityA->hasComponent<Collider>() && e.entityB->hasComponent<Collider>())) return;

    auto& colliderA = e.entityA->getComponent<Collider>();
    auto& colliderB = e.entityB->getComponent<Collider>();

    if (colliderA.tag == "player" && colliderB.tag == "enemy") {
        player = e.entityA;
        enemy = e.entityB;
    }
    else if (colliderA.tag == "enemy" && colliderB.tag == "player") {
        player = e.entityB;
        enemy = e.entityA;
    }
    else return;

    if (player->getComponent<Player>().item == Item::Weapon) {
        enemy->destroy();
        player->getComponent<Player>().item = Item::None;
    } else {
        Game::onSceneChangeRequest("lose");
    }
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
