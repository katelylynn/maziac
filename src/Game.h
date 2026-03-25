/*
 *  Game.h
 *
 */

#pragma once
#include <SDL3/SDL.h>

#include "World.h"
#include "manager/SceneManager.h"

class Game {
public:
    Game();
    ~Game();

    // these are the types that SDL uses
    void init(const char* title);

    // game loop functions
    void handleEvents(); // checks for input and system events
    void update(float deltaTime); // handles the game logic and changes to game state
    void render(); // handles the drawing of the current game state to the screen

    // used to free resources
    void destroy();

    bool running() {
        return isRunning;
    }

    SDL_Renderer* renderer = nullptr;

    SceneManager sceneManager;
    // when change scene, must go through game and game will do the actual scene change
    static std::function<void(std::string)> onSceneChangeRequest;

private:
    int frameCount = 0;
    bool isRunning = false;

    SDL_Window* window = nullptr;

    // SDL listens to the OS for input events internally and adds them to a queue
    SDL_Event event;
};
