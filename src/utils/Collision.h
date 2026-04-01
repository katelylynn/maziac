/*
 *  Collision.h
 *  Defines the AABB methods.
 */

#ifndef MAZIAC_COLLISION_H
#define MAZIAC_COLLISION_H
#include <SDL3/SDL_rect.h>

#include "Component.h"

class Collision {
public:
    // axis-aligned bounding box
    static bool AABB(const SDL_FRect rectA, const SDL_FRect& rectB);
    static bool AABB(const Collider& colA, const Collider& colB);
};

#endif //MAZIAC_COLLISION_H