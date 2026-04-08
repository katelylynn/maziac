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
            onEnemyCollision(static_cast<const CollisionEvent&>(e), world);
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

void EventResponseSystem::onEnemyCollision(const CollisionEvent& e, World& world) {
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

    EnergyState* energyState = nullptr;
    for (auto& entity : world.getEntities()) {
        if (entity->hasComponent<EnergyState>()) energyState = &entity->getComponent<EnergyState>();
    }
    if (energyState == nullptr) return;

    player->removeComponent<Velocity>();
    player->getComponent<Translation>().startPosition = player->getComponent<Translation>().endPosition;
    player->getComponent<Player>().fighting = true;

    if (player->getComponent<Player>().item == Item::Weapon) {
        playFightAnimationSequence(player, true, energyState);
    } else {
        playFightAnimationSequence(player, false, energyState);
    }

    enemy->destroy();
}

void EventResponseSystem::playFightAnimationSequence(Entity* player, bool hasWeapon, EnergyState* energyState) {
        // update the player animation
        player->removeComponent<Animation>();
        Animation animation = AssetManager::getAnimation("fight");
        animation.repeating = false;
        animation.currentClip = "fight";

        const char* animPath;
        if (hasWeapon) {
            animPath = "asset/animations/fight_weapon_anim.png";
            energyState->energyDepletionRate *= energyState->fightWithWeaponDepletionAmount;
            player->getComponent<Player>().item = Item::None;
        } else {
            animPath = "asset/animations/fight_anim.png";
            energyState->energyDepletionRate *= energyState->fightNoWeaponDepletionAmount;
        }

        SDL_Texture* playerTexture = TextureManager::load(animPath);
        SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
        SDL_FRect playerDest { player->getComponent<Transform>().position.x, player->getComponent<Transform>().position.y, 16, 16 };
        player->addComponent<Sprite>(playerTexture, playerSrc, playerDest);

        animation.onAnimationFinished = [player, animPath, energyState]() {
            player->removeComponent<Animation>();
            Animation animation = AssetManager::getAnimation("fight");
            animation.repeating = false;

            // reset the energy loss
            energyState->energyDepletionRate = energyState->initialEnergyDepletionRate;

            bool won;
            if (energyState->energy > 0.0f) {
                won = true;
                animation.currentClip = "diver_win";
            } else {
                won = false;
                animation.currentClip = "enemy_win";
            }

            SDL_Texture* playerTexture = TextureManager::load(animPath);
            SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
            SDL_FRect playerDest { player->getComponent<Transform>().position.x, player->getComponent<Transform>().position.y, 16, 16 };
            player->addComponent<Sprite>(playerTexture, playerSrc, playerDest);

            animation.onAnimationFinished = [player, won, energyState]() {
                if (!won) {
                    Game::onSceneChangeRequest("lose");
                    return;
                }

                player->removeComponent<Animation>();
                Animation animation = AssetManager::getAnimation("character");
                animation.repeating = true;

                const char* path;
                if (player->getComponent<Player>().item == Item::Treasure)
                    path = "asset/animations/diver_treasure_anim.png";
                else
                    path = "asset/animations/diver_anim.png";

                SDL_Texture* playerTexture = TextureManager::load(path);
                SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0]; // just use first frame
                SDL_FRect playerDest { player->getComponent<Transform>().position.x, player->getComponent<Transform>().position.y, 16, 16 };
                player->addComponent<Sprite>(playerTexture, playerSrc, playerDest);
                player->addComponent<Animation>(animation);

                // add back the velocity
                player->addComponent<Velocity>(Vector2D{0.0f, 0.0f}, 20.0f);

                // set status to not fighting
                player->getComponent<Player>().fighting = false;
            };
            player->addComponent<Animation>(animation);
        };
        player->addComponent<Animation>(animation);
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
