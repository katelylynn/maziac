/*
 *  UIRenderSystem.h
 *  Same as render system with the difference that world space isn't converted to screen space.
 */

#ifndef MAZIAC_UIRENDERSYSTEM_H
#define MAZIAC_UIRENDERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "RenderUtils.h"
#include "../../manager/TextureManager.h"

class UIRenderSystem {
public:
    void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                auto transform = entity->getComponent<Transform>();
                auto sprite = entity->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::UI) continue;

                // no converting from world space to screen space
                sprite.dest.x = transform.position.x;
                sprite.dest.y = transform.position.y;

                if (sprite.visible) {
                    SDL_FRect scaledDest = RenderUtils::getScaledDest(sprite.dest, transform.scale);
                    TextureManager::draw(sprite.texture, sprite.src, scaledDest);
                }
            }
        }
    }
};

#endif //COMP8051_UIRENDERSYSTEM_H