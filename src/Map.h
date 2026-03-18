//
// Created by kate on 2026-01-14.
//

#ifndef COMP8051_MAP_H
#define COMP8051_MAP_H

#include <vector>
#include <SDL3/SDL.h>
#include <Component.h>

class Map {
public:
    Map() = default;
    ~Map() = default;

    void load(const char *path, SDL_Texture *ts);
    void draw(const Camera &camera);

    SDL_Texture *tileset = nullptr;
    int width{}, height{};

    // map data
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> itemColliders;
    std::vector<Collider> colliders;
};

#endif //COMP8051_MAP_H