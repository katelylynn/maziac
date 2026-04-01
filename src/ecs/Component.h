/*
 *  Component.h
 *  Defines all structs and their data members.
 */

#ifndef MAZIAC_COMPONENT_H
#define MAZIAC_COMPONENT_H
#include <functional>
#include <SDL3/SDL_render.h>

#include "Vector2D.h"
#include <string>
#include <unordered_map>

#include "AnimationClip.h"
#include "Entity.h"

// ENUMS

enum class RenderLayer {
    World,
    UI
};

// STRUCTS

struct Animation {
    // key = walk left, walk right, idle right, etc.
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{}; // time is accumulated for the current frame
    int currentFrame{}; // index of the current frame in the clip
    float speed = 0.8f; // time per frame
};

struct Children {
    std::vector<Entity*> children{};
};

struct Clickable {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};
    bool pressed = false;
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    Vector2D offset{};
    bool enabled = true;
};

struct Parent {
    Entity* parent = nullptr;
};

struct SceneState {
    int energy = 0;
};

struct Spawnpoint {
    Vector2D position{};
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dest{};
    RenderLayer renderLayer = RenderLayer::World;
    bool visible = true;
};

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

struct Velocity {
    Vector2D direction{};
    float speed{};
};

// TAGS

struct PlayerTag{};
struct ProjectileTag{};

#endif //MAZIAC_COMPONENT_H