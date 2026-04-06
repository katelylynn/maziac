/*
 *  RenderSystem.h
 *  Draws the sprite and optionally the collider's border.
 */

#ifndef MAZIAC_RENDERSYSTEM_H
#define MAZIAC_RENDERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "../../manager/TextureManager.h"

class RenderSystem {
public:
    void render(const std::vector<std::unique_ptr<Entity>>& entities, Map& map) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                // referenced versions to not create copies
                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::World) continue;

                sprite.dest.x = t.position.x;
                sprite.dest.y = t.position.y;

                // if entity has animation, update the source rect
                if (entity->hasComponent<Animation>()) {
                    auto& animation = entity->getComponent<Animation>();
                    sprite.src = animation.clips[animation.currentClip].frameIndices[animation.currentFrame];
                }

                // don't draw the entity if they are too far from the player
                Entity* player = nullptr;

                for (auto& e : entities) {
                    if (e->hasComponent<Player>()) {
                        player = e.get();
                        break;
                    }
                }

                if (player == nullptr) return;
                Transform playerTransform = player->getComponent<Transform>();

                if (
                    std::abs(playerTransform.position.x - t.position.x) +
                    std::abs(playerTransform.position.y - t.position.y) >
                    // position + half a tile slack
                    player->getComponent<Player>().viewDistance * map.tileWidth + map.tileWidth * 0.5f
                )
                    continue;

                TextureManager::draw(sprite.texture, sprite.src, sprite.dest);

                // OPTIONAL, draws the border of the collider
                // if (entity->hasComponent<Collider>()) {
                //     TextureManager::drawBorder(entity->getComponent<Collider>().rect);
                // }
            }
        }
    }
};

#endif //MAZIAC_RENDERSYSTEM_H