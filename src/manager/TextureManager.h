/*
 *  TextureManager.h
 *  Defines texture-related methods.
 */

#ifndef MAZIAC_TEXTUREMANAGER_H
#define MAZIAC_TEXTUREMANAGER_H

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

#endif //MAZIAC_TEXTUREMANAGER_H