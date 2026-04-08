/*
 *  PathIlluminationSystem.h
 */

#ifndef MAZIAC_PATHILLUMINATIONSYSTEM_H
#define MAZIAC_PATHILLUMINATIONSYSTEM_H
#include <SDL3/SDL_timer.h>

#include "Component.h"

class PathIlluminationSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, Map& map) {
        Entity* sceneState;
        for (auto& entity : entities) {
            if (entity->hasComponent<SceneState>()) sceneState = entity.get();
        }
        if (!sceneState) return;

        for (std::pair<Uint64, std::vector<Vector2D>> path : map.paths) {
            Uint64 test = SDL_GetTicks();
            if (test - path.first > sceneState->getComponent<SceneState>().pathIllumuniationDuration) {
                for (Vector2D tile : path.second) {
                    map.pathData[tile.y][tile.x] = 0;
                }
                map.paths.erase(path.first);
            } else {
                for (Vector2D tile : path.second) {
                    map.pathData[tile.y][tile.x] = 1;
                }
            }
        }
    }
};

#endif //MAZIAC_PATHILLUMINATIONSYSTEM_H