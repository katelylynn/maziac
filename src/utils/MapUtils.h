/*
 *  MapUtils.h
 */

#ifndef MAZIAC_MAPUTILS_H
#define MAZIAC_MAPUTILS_H
#include <vector>

#include "Vector2D.h"

class MapUtils {
public:
    static std::vector<Vector2D> shortestPath(
        const std::vector<std::vector<int>>& map,
        const Vector2D& startTile,
        const Vector2D& goalTile
    ) {
        return shortestPathRecursive(map, std::vector<Vector2D>{}, startTile, goalTile);
    }
private:
    static std::vector<Vector2D> shortestPathRecursive(
        const std::vector<std::vector<int>>& map,
        std::vector<Vector2D> visited,
        const Vector2D& currentTile,
        const Vector2D& goalTile
    ) {
        visited.push_back(currentTile);

        std::vector<Vector2D> min;
        std::vector<Vector2D> curr;

        // north
        Vector2D north = Vector2D(currentTile.x, currentTile.y - 1);
        if (north == goalTile) return {currentTile};
        if (
            !contains(visited, north) &&
            north.y >= 0 &&
            map[north.y][north.x] == 0
        )
            min = shortestPathRecursive(map, visited, north, goalTile);

        // east
        Vector2D east = Vector2D(currentTile.x + 1, currentTile.y);
        if (east == goalTile) return {currentTile};
        if (
            !contains(visited, east) &&
            east.x < map[0].size() &&
            map[east.y][east.x] == 0
        ) {
            curr = shortestPathRecursive(map, visited, east, goalTile);
            if (min.empty() || curr.size() < min.size()) min = curr;
        }

        // south
        Vector2D south = Vector2D(currentTile.x, currentTile.y + 1);
        if (south == goalTile) return {currentTile};
        if (
            !contains(visited, south) &&
            south.y < map.size() &&
            map[south.y][south.x] == 0
        ) {
            curr = shortestPathRecursive(map, visited, south, goalTile);
            if (min.empty() || curr.size() < min.size()) min = curr;
        }

        // west
        Vector2D west = Vector2D(currentTile.x - 1, currentTile.y);
        if (west == goalTile) return {currentTile};
        if (
            !contains(visited, west) &&
            west.x >= 0 &&
            map[west.y][west.x] == 0
        ) {
            curr = shortestPathRecursive(map, visited, west, goalTile);
            if (min.empty() || curr.size() < min.size()) min = curr;
        }

        min.insert(min.begin(), currentTile);
        return min;
    }
    static bool contains(std::vector<Vector2D>& vector, Vector2D item) {
        for (Vector2D curr : vector) {
            if (item == curr) return true;
        }
        return false;
    }
};

#endif //MAZIAC_MAPUTILS_H