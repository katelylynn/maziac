/*
 *  AnimationClip.h
 *  Defines a struct to store an animation's frames.
 */

#ifndef MAZIAC_ANIMATIONCLIP_H
#define MAZIAC_ANIMATIONCLIP_H
#include <vector>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndices;
};

#endif //MAZIAC_ANIMATIONCLIP_H