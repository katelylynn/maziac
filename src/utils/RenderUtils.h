/*
 *  RenderUtils.h
 *  Helps with render scaling math.
 */

#ifndef MAZIAC_RENDERUTILS_H
#define MAZIAC_RENDERUTILS_H
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

#endif //MAZIAC_RENDERUTILS_H