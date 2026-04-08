/*
 *  Map.h
 *  Defines the load/draw functions, dimensions, tile layers and spawn points.
 */

#ifndef MAZIAC_MAP_H
#define MAZIAC_MAP_H

#include <vector>
#include <Component.h>
#include <map>
#include <memory>

class Map {
public:
    void load(const char *path, SDL_Texture *ts);
    void draw(const std::vector<std::unique_ptr<Entity>>& entities);
    void illuminate(Vector2D startTile);

    // the tileset to paint tiles with
    SDL_Texture *tileset = nullptr;

    // dimensions
    int mapWidth{}, mapHeight{}, tileWidth{}, tileHeight{};

    // type alias
    using grid = std::vector<std::vector<int>>;

    // layer to name
    // walls intentionally placed last
    std::vector<std::pair<std::string, grid*>> layers = {
        {"energy", &energyData},
        {"guide", &guideData},
        {"weapon", &weaponData},
        {"treasure", &treasureData},
        {"exit", &exitData},
        {"wall", &wallData}
    };

    // map layer data
    grid wallData;
    grid energyData;
    grid energyBarData;
    grid guideData;
    grid weaponData;
    grid treasureData;
    grid exitData;

    // pathing
    grid pathData;
    std::pair<Uint64, std::vector<Vector2D>> illuminatedPath{}; // the currently illuminated path and its activation time

    // energy bar tiles
    std::vector<bool> energyBar;

    // map spawn data
    Spawnpoint playerSpawnpoint{};
    std::vector<Spawnpoint> enemySpawnpoints{};

private:
    void parseLayer(std::vector<std::vector<int>> &layer, auto* data);
};

#endif //MAZIAC_MAP_H