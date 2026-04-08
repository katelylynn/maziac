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
        // if no illuminated path
        if (map.illuminatedPath.second.size() == 0) return;

        Entity* sceneState;
        for (auto& entity : entities) {
            if (entity->hasComponent<SceneState>()) sceneState = entity.get();
        }
        if (!sceneState) return;

        if (SDL_GetTicks() - map.illuminatedPath.first > sceneState->getComponent<SceneState>().pathIllumuniationDuration) {
            for (Vector2D tile : map.illuminatedPath.second) {
                map.pathData[tile.y][tile.x] = 0;
            }
            map.illuminatedPath = {};
        } else {
            for (Vector2D tile : map.illuminatedPath.second) {
                map.pathData[tile.y][tile.x] = 1;
            }
        }
    }
};

#endif //MAZIAC_PATHILLUMINATIONSYSTEM_H