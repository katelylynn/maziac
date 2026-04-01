/*
 *  MouseInputSystem.h
 *  Defines update function for the mouse input system.
 */

#ifndef MAZIAC_MOUSEINPUTSYSTEM_H
#define MAZIAC_MOUSEINPUTSYSTEM_H
#include <SDL3/SDL_events.h>

class World;

class MouseInputSystem {
public:
    void update(World& world, const SDL_Event& event);
};

#endif //MAZIAC_MOUSEINPUTSYSTEM_H