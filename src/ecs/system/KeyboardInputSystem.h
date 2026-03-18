//
// Created by kate on 2026-01-28.
//

#ifndef COMP8051_KEYBOARDINPUTSYSTEM_H
#define COMP8051_KEYBOARDINPUTSYSTEM_H
#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>

#include "Component.h"
#include "Entity.h"

class KeyboardInputSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const SDL_Event& event) {
        // SDL event will tell us if a key is pressed down

        for (auto& e : entities) {
            if (e->hasComponent<PlayerTag>() && e->hasComponent<Velocity>()) {
                auto& v = e->getComponent<Velocity>();

                if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = -1;
                            break;
                        case SDLK_S:
                            v.direction.y = 1;
                            break;
                        case SDLK_A:
                            v.direction.x = -1;
                            break;
                        case SDLK_D:
                            v.direction.x = 1;
                            break;
                        default:
                            break;
                    }
                }

                if (event.type == SDL_EVENT_KEY_UP) {
                    switch (event.key.key) {
                        case SDLK_W:
                            v.direction.y = 0;
                            break;
                        case SDLK_S:
                            v.direction.y = 0;
                            break;
                        case SDLK_A:
                            v.direction.x = 0;
                            break;
                        case SDLK_D:
                            v.direction.x = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
};

#endif //COMP8051_KEYBOARDINPUTSYSTEM_H