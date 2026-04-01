/*
 *  Map.h
 *  Defines the load/draw functions, dimensions, tile layers and spawn points.
 */

#ifndef MAZIAC_MAP_H
#define MAZIAC_MAP_H

#include <vector>
#include <Component.h>

class Map {
public:
    void load(const char *path, SDL_Texture *ts);
    void draw();

    // the tileset to paint tiles with
    SDL_Texture *tileset = nullptr;

    // dimensions
    int mapWidth{}, mapHeight{}, tileWidth{}, tileHeight{};

    // map layer data
    std::vector<std::vector<int>> wallData;
    std::vector<std::vector<int>> energyData;
    std::vector<std::vector<int>> guideData;
    std::vector<std::vector<int>> weaponData;
    std::vector<std::vector<int>> treasureData;
    std::vector<std::vector<int>> exitData;

    // map spawn data
    Spawnpoint playerSpawnpoint{};
    std::vector<Spawnpoint> enemySpawnpoints{};

private:
    void parseLayer(std::vector<std::vector<int>> &layer, auto* data);
};

#endif //MAZIAC_MAP_H