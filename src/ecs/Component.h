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

enum class Item {
    None,
    Treasure,
    Weapon
};

// STRUCTS

struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{}; // key = walk left, idle right, etc.
    std::string currentClip{};
    float time{}; // time is accumulated for the current frame
    int currentFrame{}; // index of the current frame in the clip
    float speed = 0.4f; // time per frame

    bool repeating = false;
    std::function<void()> onAnimationFinished{}; // if not repeating
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    Vector2D offset{};
    bool enabled = true;
};

struct Enemy {
    Vector2D startingPosition{};
    int wanderRange = 2;
    Uint64 currentWait = 5000.0f;
    Uint64 maxWait = 5000.0f; // how long to wait between movements
};

struct EnergyState {
    float energy = 100.0f;
    float initialEnergy = 100.0f;
    float energyBoostAmount = 40.0f;

    // ENERGY DEPLETION
    float energyDepletionRate = 1.0f;
    float initialEnergyDepletionRate = 2.0f;
    float fightNoWeaponDepletionAmount = 15.0f;
    float fightWithWeaponDepletionAmount = 5.0f;
};

template<typename T>
struct Observer {
    T* currValue{};
    T oldValue{};
    std::function<void()> onValueChange{};
};

struct Player {
    Item item = Item::None;
    int viewDistance = 3; // how many squares away the player can see
    bool fighting = false;
};

struct SceneState {
    Uint64 pathIllumuniationDuration = 5000.0f; // in seconds
};

struct Spawnpoint {
    Vector2D position{};
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dest{};
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

#endif //MAZIAC_COMPONENT_H