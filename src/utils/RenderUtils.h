//
// Created by kate on 2026-03-12.
//

#ifndef COMP8051_RENDERUTILS_H
#define COMP8051_RENDERUTILS_H
#include <SDL3/SDL_rect.h>

class RenderUtils {
public:
    // scaling from center point
    // example: slightly scaling a button to show that it's been clicked
    static SDL_FRect getScaledDest(const SDL_FRect& dest, float scale) {
        return SDL_FRect(
            dest.x + dest.w * (1 - scale) / 2,
            dest.y + dest.h * (1 - scale) / 2,
            dest.w * scale,
            dest.h * scale
        );
    }
};

#endif //COMP8051_RENDERUTILS_H