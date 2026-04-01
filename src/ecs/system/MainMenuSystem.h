/*
 *  MainMenuSystem.h
 *  Defines the update function for the main menu functionality.
 */

#ifndef MAZIAC_MAINMENUSYSTEM_H
#define MAZIAC_MAINMENUSYSTEM_H
#include <SDL3/SDL_events.h>

class MainMenuSystem {
public:
    void update(const SDL_Event& event);
};

#endif //MAZIAC_MAINMENUSYSTEM_H