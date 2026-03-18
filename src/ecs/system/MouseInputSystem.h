//
// Created by kate on 2026-03-12.
//

#ifndef COMP8051_MOUSEINPUTSYSTEM_H
#define COMP8051_MOUSEINPUTSYSTEM_H
#include <SDL3/SDL_events.h>

class World;

class MouseInputSystem {
public:
    void update(World& world, const SDL_Event& event);
};

#endif //COMP8051_MOUSEINPUTSYSTEM_H