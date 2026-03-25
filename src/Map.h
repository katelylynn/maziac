/*
 *  Map.h
 *  Defines the functions, tile layers and spawnpoints.
 */

#ifndef MAZIAC_MAP_H
#define MAZIAC_MAP_H

#include <vector>
#include <Component.h>

class Map {
public:
    void load(const char *path, SDL_Texture *ts);

    // TODO
    void generate(SDL_Texture *ts);
    void draw(const Camera &camera);

    // the tileset to paint tiles with
    SDL_Texture *tileset = nullptr;

    // dimensions
    int mapWidth{}, mapHeight{}, tileWidth{}, tileHeight{};

    // map layer data
    std::vector<std::vector<int>> oceanData;
    std::vector<std::vector<int>> wallData;
    std::vector<std::vector<int>> energyData;
    std::vector<std::vector<int>> guideData;
    std::vector<std::vector<int>> weaponData;
    std::vector<std::vector<int>> treasureData;

    // map spawn data
    Spawnpoint playerSpawnpoint{};
    std::vector<Spawnpoint> enemySpawnpoints{};

private:
    void parseLayer(std::vector<std::vector<int>> &layer, auto* data);
};

#endif //MAZIAC_MAP_H