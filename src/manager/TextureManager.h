//
// Created by kate on 2026-01-14.
//

#ifndef COMP8051_TEXTUREMANAGER_H
#define COMP8051_TEXTUREMANAGER_H

#include <string>
#include <unordered_map>

#include "SDL3_image/SDL_image.h"

class TextureManager {
    static std::unordered_map<std::string, SDL_Texture*> textures;
public:
    static SDL_Texture* load(const char* path);

    // floating point Rects
    static void draw(SDL_Texture* texture, SDL_FRect src, SDL_FRect dst);

    // for debugging colliders
    static void drawBorder(SDL_FRect rect);

    static void clean();
};

#endif //COMP8051_TEXTUREMANAGER_H