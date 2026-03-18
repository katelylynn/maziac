//
// Created by kate on 2026-03-11.
//

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

            onCollision(collision, "item", world);
            onCollision(collision, "wall", world);
            onCollision(collision, "projectile", world);
        }
    );

    // player action subscription
    world.getEventManager().subscribe(
        [this, &world](const BaseEvent& e) {

            if (e.type != EventType::PlayerAction) return;

            // cast base type to player action type
            const auto& playerAction = static_cast<const PlayerActionEvent&>(e);

            // TODO onPlayerAction
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

void EventResponseSystem::onCollision(
    const CollisionEvent& e,
    const char *otherTag,
    World& world
) {

    Entity* player = nullptr;
    Entity* other = nullptr;

    if (!getCollisionEntities(e, otherTag, player, other)) return;

    if (std::string(otherTag) == "item") {
        // we are defining instant behavior, not ongoing behavior
        if (e.state != CollisionState::Enter) return;

        other->destroy();

        for (auto& entity : world.getEntities()) {
            if (!entity->hasComponent<SceneState>()) continue;

            auto& sceneState = entity->getComponent<SceneState>();
            sceneState.coinsCollected++;
            if (sceneState.coinsCollected > 1) {
                Game::onSceneChangeRequest("level2");
            }
        }
    }
    else if (std::string(otherTag) == "wall") {
        // stay bc need to constantly check if player colliding w wall
        if (e.state != CollisionState::Stay) return;

        auto& t = player->getComponent<Transform>();
        t.position = t.oldPosition;
    }
    else if (std::string(otherTag) == "projectile") {
        // without filtering for enter, the collision would happen a bunch of times and immediately bring the player's health to zero
        if (e.state != CollisionState::Enter) return;

        // simple, but ideally we would only operate on data in an update function
        // (hinting at transient entities, e.g. damage entities)
        auto& health = player->getComponent<Health>();
        health.currentHealth--;

        Game::gameState.playerHealth = health.currentHealth;

        std::cout << health.currentHealth << std::endl;
        if (health.currentHealth <= 0) {
            player->destroy();
            Game::onSceneChangeRequest("gameover");
        }
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
