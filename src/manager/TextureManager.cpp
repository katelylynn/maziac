//
// Created by kate on 2026-01-14.
//

#include "TextureManager.h"

#include <iostream>

#include "../Game.h"

// doesn't create any extra memory, just grabs the reference of this object
extern Game* game;
std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

// load our texture with a path
SDL_Texture* TextureManager::load(const char* path) {
    // caching: storing the result of some work so you don't have to repeat the work next time
    // check if the texture already exists in the map
    auto it = textures.find(path);

    // if the iterator is not at the end...
    if (it != textures.end()) {
        // return it
        // first (key) is path, second (value) is the texture
        return it->second;
    }

    // a surface represents an image in RAM (CPU memory)
    // allows us to modify the image before we store it in GPU
    SDL_Surface* tempSurface = IMG_Load(path);

    if (!tempSurface) {
        std::cout << "Failed to load image " << path << std::endl;
    }

    // a texture represents an image in VRAM (GPU memory)
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    // cleanup surface
    SDL_DestroySurface(tempSurface);

    // check if the texture creation was successful
    if (!texture) {
        std::cout << "Failed to create texture from " << path << std::endl;
        return nullptr;
    }

    // store the new texture in the cache
    textures[path] = texture;

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst) {
    // when scaled up, tells each pixel to become a bigger block instead of blurring
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    // draw the texture to the screen from the VRAM
    SDL_RenderTexture(game->renderer, texture, &src, &dst);
}

void TextureManager::drawBorder(SDL_FRect rect) {
    SDL_RenderRect(game->renderer, &rect);
}

void TextureManager::clean() {
    for (auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
        texture.second = nullptr;
    }
    textures.clear();
}
