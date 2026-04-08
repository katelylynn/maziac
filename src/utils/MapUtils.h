/*
 *  MapUtils.h
 */

#ifndef MAZIAC_MAPUTILS_H
#define MAZIAC_MAPUTILS_H
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "Vector2D.h"

class MapUtils {
public:
    static std::vector<Vector2D> shortestPath(
        const std::vector<std::vector<int>>& map,
        const Vector2D& startTile,
        const Vector2D& goalTile
    ) {
        std::queue<Vector2D> queue;
        queue.push(startTile);

        std::set<Vector2D> visited;
        visited.insert(startTile);

        std::map<Vector2D, Vector2D> parent;

        while (!queue.empty()) {
            Vector2D currTile = queue.front();
            queue.pop();

            std::vector neighbors = {
                Vector2D(currTile.x, currTile.y - 1), // north
                Vector2D(currTile.x + 1, currTile.y), // east
                Vector2D(currTile.x, currTile.y + 1), // south
                Vector2D(currTile.x - 1, currTile.y)  // west
            };

            for (const Vector2D& next : neighbors) {
                if (next == goalTile) {
                    std::vector<Vector2D> path;
                    Vector2D curr = goalTile;
                    parent[next] = currTile;

                    while (curr != startTile) {
                        path.push_back(curr);
                        curr = parent[curr];
                    }
                    path.push_back(startTile);

                    std::reverse(path.begin(), path.end());
                    return path;
                }

                if (
                    next.y >= 0 &&
                    next.y < map.size() &&
                    next.x >= 0 &&
                    next.x < map[0].size() &&
                    map[next.y][next.x] == 0 &&
                    visited.find(next) == visited.end()
                ) {
                    queue.push(next);
                    visited.insert(next);
                    parent[next] = currTile;
                }
            }
        }

        return {};
    }
};

#endif //MAZIAC_MAPUTILS_H