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
    void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                // referenced versions to not create copies
                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::World) continue;

                // convert from world space to screen space
                sprite.dest.x = t.position.x;
                sprite.dest.y = t.position.y;

                // if entity has animation, update the source rect
                if (entity->hasComponent<Animation>()) {
                    auto& animation = entity->getComponent<Animation>();
                    sprite.src = animation.clips[animation.currentClip].frameIndices[animation.currentFrame];
                }

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