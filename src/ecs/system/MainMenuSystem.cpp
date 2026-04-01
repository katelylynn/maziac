/*
 *  MainMenuSystem.cpp
 *  Defines what happens on key presses when on the main menu.
 *  Necessary to have a cpp file because the compiler must already know that Game:: is a class.
 */

#include "MainMenuSystem.h"

#include "Game.h"

void MainMenuSystem::update(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
            case SDLK_SPACE:
                Game::onSceneChangeRequest("level1");
                break;
            default:
                break;
        }
    }
}
