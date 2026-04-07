/*
 *  TileInteractionSystem.cpp
 */

#include "TileInteractionSystem.h"

#include "Game.h"
#include "event/BaseEvent.h"

TileInteractionSystem::TileInteractionSystem(World &world) {
    // collision subscription
    world.getEventManager().subscribe(
        [this, &world](const BaseEvent& e) {
            if (e.type != EventType::Collision) return;

            // cast base type to collision type
            const auto& collision = static_cast<const CollisionEvent&>(e);

            if (collision.state != CollisionState::Enter) return;

            Entity* player = nullptr;
            Entity* tile = nullptr;

            if (!getCollisionEntities(collision, player, tile)) return;

            // prevents swimming into the wall
            player->getComponent<Transform>().position =
                player->getComponent<Translation>().endPosition =
                player->getComponent<Translation>().startPosition;

            // prevents calling the same collision multiple times
            if (currentWait > 0.0f) return;
            currentWait = maxWait;

            std::string tileTag = tile->getComponent<Collider>().tag;

            if (tileTag == "energy") onEnergyCollision(tile, world);
            if (tileTag == "weapon") onWeaponCollision(player, tile, world);
            if (tileTag == "treasure") onTreasureCollision(player, tile, world);

            // exit
            if (tileTag == "exit" && player->getComponent<Player>().item == Item::Treasure) {
                std::cout << "exit" << std::endl;
                Game::onSceneChangeRequest("win");
            }
        }
    );
}

void TileInteractionSystem::update(float deltaTime) {
    currentWait -= deltaTime;
}

bool TileInteractionSystem::getCollisionEntities(const CollisionEvent &e, Entity *&player, Entity *&other) {
    // check both entities exist
    if (e.entityA == nullptr || e.entityB == nullptr)
        return false;

    // check both entities have colliders
    if (!(e.entityA->hasComponent<Collider>() && e.entityB->hasComponent<Collider>()))
        return false;

    auto& colliderA = e.entityA->getComponent<Collider>();
    auto& colliderB = e.entityB->getComponent<Collider>();

    if (colliderA.tag == "player") {
        player = e.entityA;
        other = e.entityB;
    }
    else if (colliderB.tag == "player") {
        player = e.entityB;
        other = e.entityA;
    }

    return player && other;
}

void TileInteractionSystem::onEnergyCollision(Entity *tile, World &world) {
    // find scene state
    EnergyState* energyState = nullptr;
    for (auto& entity : world.getEntities()) {
        if (!entity->hasComponent<EnergyState>()) continue;
        energyState = &entity->getComponent<EnergyState>();
    }

    // return if it can't find energy state
    if (energyState == nullptr) {
        std::cout << "No energy state!" << std::endl;
        return;
    }

    // add energy boost
    energyState->energy += energyState->energyBoostAmount;

    // cap energy at the limit
    if (energyState->energy > energyState->initialEnergy) energyState->energy = energyState->initialEnergy;

    // change the energy collider to a wall collider
    tile->getComponent<Collider>().tag = "wall";

    // change the energy sprite to a wall sprite
    Transform otherTransform = tile->getComponent<Transform>();
    int row = otherTransform.position.y / world.getMap().tileHeight;
    int col = otherTransform.position.x / world.getMap().tileWidth;
    world.getMap().energyData[row][col] = 0;
}

void TileInteractionSystem::onWeaponCollision(Entity *player, Entity *tile, World &world) {
    // check if player is already holding something
    if (player->getComponent<Player>().item == Item::Treasure) {
        tile->getComponent<Collider>().tag = "treasure";

        // change the weapon sprite to a treasure sprite
        Transform otherTransform = tile->getComponent<Transform>();
        int row = otherTransform.position.y / world.getMap().tileHeight;
        int col = otherTransform.position.x / world.getMap().tileWidth;
        world.getMap().weaponData[row][col] = 0;

        world.getMap().treasureData[row][col] = 1;
    }
    else if (player->getComponent<Player>().item == Item::None) {
        // change the weapon collider to a wall collider
        tile->getComponent<Collider>().tag = "wall";

        // change the weapon sprite to a wall sprite
        Transform otherTransform = tile->getComponent<Transform>();
        int row = otherTransform.position.y / world.getMap().tileHeight;
        int col = otherTransform.position.x / world.getMap().tileWidth;
        world.getMap().weaponData[row][col] = 0;
    }

    // update the player
    player->getComponent<Player>().item = Item::Weapon;

    // update the player's spritesheet
    player->getComponent<Sprite>().texture = TextureManager::load("../asset/animations/diver_weapon_anim.png");
}

void TileInteractionSystem::onTreasureCollision(Entity *player, Entity *tile, World &world) {
    // check if player is already holding something
    if (player->getComponent<Player>().item == Item::Weapon) {
        tile->getComponent<Collider>().tag = "weapon";

        Transform otherTransform = tile->getComponent<Transform>();
        int row = otherTransform.position.y / world.getMap().tileHeight;
        int col = otherTransform.position.x / world.getMap().tileWidth;
        world.getMap().treasureData[row][col] = 0;

        world.getMap().weaponData[row][col] = 2;
    }
    else if (player->getComponent<Player>().item == Item::None) {
        tile->getComponent<Collider>().tag = "wall";

        Transform otherTransform = tile->getComponent<Transform>();
        int row = otherTransform.position.y / world.getMap().tileHeight;
        int col = otherTransform.position.x / world.getMap().tileWidth;
        world.getMap().treasureData[row][col] = 0;
    }

    // update the player
    player->getComponent<Player>().item = Item::Treasure;

    // update the player's spritesheet
    player->getComponent<Sprite>().texture = TextureManager::load("../asset/animations/diver_treasure_anim.png");
}
