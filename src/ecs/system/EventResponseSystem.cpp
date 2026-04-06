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
        [this, &world](const BaseEvent& e) {
            if (e.type != EventType::Collision) return;

            // cast base type to collision type
            const auto& collision = static_cast<const CollisionEvent&>(e);

            bool resolved = false;

            if (!resolved) onCollision(collision, "enemy", world, &resolved);
            if (!resolved) onCollision(collision, "wall", world, &resolved);
            if (!resolved) onCollision(collision, "energy", world, &resolved);
            if (!resolved) onCollision(collision, "weapon", world, &resolved);
            if (!resolved) onCollision(collision, "treasure", world, &resolved);
            if (!resolved) onCollision(collision, "exit", world, &resolved);
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
    World& world,
    bool* resolved
) {
    Entity* player = nullptr;
    Entity* other = nullptr;

    if (!getCollisionEntities(e, otherTag, player, other)) return;

    // ENEMY:
    if (std::string(otherTag) == "enemy") {
        if (player->getComponent<Player>().item == Item::Weapon) {
            other->destroy();
            // player->getComponent<Player>().item = Item::None;
        } else {
            Game::onSceneChangeRequest("lose");
        }
    }

    // WALL:

    // only continues if "Enter" state
    if (e.state != CollisionState::Stay) return;

    auto& transform = player->getComponent<Transform>();
    auto& translation = player->getComponent<Translation>();

    // prevents swimming into the wall
    transform.position = translation.endPosition = translation.startPosition;

    // find scene state
    EnergyState* energyState = nullptr;
    for (auto& entity : world.getEntities()) {
        if (!entity->hasComponent<EnergyState>()) continue;
        energyState = &entity->getComponent<EnergyState>();
    }

    // return if can't find energy state
    if (energyState == nullptr) {
        std::cout << "No energy state!" << std::endl;
        return;
    }

    // ENERGY:

    if (std::string(otherTag) == "energy") {
        // add energy boost
        energyState->energy += energyState->energyBoostAmount;
        // cap it at the limit
        if (energyState->energy > energyState->initialEnergy) energyState->energy = energyState->initialEnergy;

        // change the energy collider to a wall collider
        other->getComponent<Collider>().tag = "wall";

        // change the energy sprite to a wall sprite
        Transform otherTransform = other->getComponent<Transform>();
        int row = otherTransform.position.y / world.getMap().tileHeight;
        int col = otherTransform.position.x / world.getMap().tileWidth;
        world.getMap().energyData[row][col] = 0;
    }

    // WEAPON:

    if (std::string(otherTag) == "weapon") {
        // check if player is already holding something
        if (player->getComponent<Player>().item == Item::Treasure) {
            other->getComponent<Collider>().tag = "treasure";
            *resolved = true;

            // change the weapon sprite to a treasure sprite
            Transform otherTransform = other->getComponent<Transform>();
            int row = otherTransform.position.y / world.getMap().tileHeight;
            int col = otherTransform.position.x / world.getMap().tileWidth;
            world.getMap().weaponData[row][col] = 0;

            world.getMap().treasureData[row][col] = 1;
        }
        else if (player->getComponent<Player>().item == Item::None) {
            // change the weapon collider to a wall collider
            other->getComponent<Collider>().tag = "wall";

            // change the weapon sprite to a wall sprite
            Transform otherTransform = other->getComponent<Transform>();
            int row = otherTransform.position.y / world.getMap().tileHeight;
            int col = otherTransform.position.x / world.getMap().tileWidth;
            world.getMap().weaponData[row][col] = 0;
        }

        // update the player
        player->getComponent<Player>().item = Item::Weapon;

        // update the player's spritesheet
        player->getComponent<Sprite>().texture = TextureManager::load("../asset/animations/diver_weapon_anim.png");
    }

    // TREASURE AND EXIT:

    if (std::string(otherTag) == "treasure") {
        // check if player is already holding something
        if (player->getComponent<Player>().item == Item::Weapon) {
            other->getComponent<Collider>().tag = "weapon";
            *resolved = true;

            Transform otherTransform = other->getComponent<Transform>();
            int row = otherTransform.position.y / world.getMap().tileHeight;
            int col = otherTransform.position.x / world.getMap().tileWidth;
            world.getMap().treasureData[row][col] = 0;

            world.getMap().weaponData[row][col] = 2;
        }
        else if (player->getComponent<Player>().item == Item::None) {
            other->getComponent<Collider>().tag = "wall";

            Transform otherTransform = other->getComponent<Transform>();
            int row = otherTransform.position.y / world.getMap().tileHeight;
            int col = otherTransform.position.x / world.getMap().tileWidth;
            world.getMap().treasureData[row][col] = 0;
        }

        // update the player
        player->getComponent<Player>().item = Item::Treasure;

        // update the player's spritesheet
        player->getComponent<Sprite>().texture = TextureManager::load("../asset/animations/diver_treasure_anim.png");
    }

    if (std::string(otherTag) == "exit" && player->getComponent<Player>().item == Item::Treasure) {
        std::cout << "exit" << std::endl;
        Game::onSceneChangeRequest("win");
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
