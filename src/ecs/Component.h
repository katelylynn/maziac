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
    float speed = 0.4f; // time per frame
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

template<typename T>
struct Observer {
    T* currValue{};
    T oldValue{};
    std::function<void()> onValueChange{};
};

struct Parent {
    Entity* parent = nullptr;
};

struct SceneState {
    float energy = 100.0f;
    float initialEnergy = 100.0f;
    float energyDepletionRate = 5.0f;
    float energyBoostAmount = 40.0f;
    bool treasure = false;
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

struct Translation {
    Vector2D startPosition{-1.0f, -1.0f};
    Vector2D endPosition{-1.0f, -1.0f};
};

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
};

struct Velocity {
    Vector2D direction{};
    float speed{};
};

// TAGS

struct PlayerTag{};
struct ProjectileTag{};

#endif //MAZIAC_COMPONENT_H