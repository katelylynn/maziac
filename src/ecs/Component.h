//
// Created by kate on 2026-01-21.
//

#ifndef COMP8051_COMPONENT_H
#define COMP8051_COMPONENT_H
#include <functional>
#include <SDL3/SDL_render.h>

#include "Vector2D.h"
#include <string>
#include <unordered_map>

#include "AnimationClip.h"
#include "Entity.h"

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

struct Spawnpoint {
    Vector2D position{};
};

struct Velocity {
    Vector2D direction{};
    float speed{};
};

enum class RenderLayer {
    World,
    UI
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dest{};
    RenderLayer renderLayer = RenderLayer::World;
    bool visible = true;
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    bool enabled = true;
};

struct Animation {
    // key = walk left, walk right, idle right, etc.
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{}; // time is accumulated for the current frame
    int currentFrame{}; // index of the current frame in the clip
    float speed = 0.8f; // time per frame
};

// our game state, might have multiple scenes
struct SceneState {
    int coinsCollected = 0;
};

struct Health {
    int currentHealth{};
};

struct Clickable {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};
    bool pressed = false;
};

struct Parent {
    Entity* parent = nullptr;
};

struct Children {
    std::vector<Entity*> children{};
};

// TAGS

struct PlayerTag{};
struct ProjectileTag{};

#endif //COMP8051_COMPONENT_H