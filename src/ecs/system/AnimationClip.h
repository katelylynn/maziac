//
// Created by kate on 2026-02-25.
//

#ifndef COMP8051_ANIMATIONCLIP_H
#define COMP8051_ANIMATIONCLIP_H
#include <vector>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndices;
};

#endif //COMP8051_ANIMATIONCLIP_H