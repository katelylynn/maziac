//
// Created by kate on 2026-01-07.
//

#pragma once
#include <SDL3/SDL.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    // game loop functions
    void handleEvents(); // checks for input and system events
    void update(); // handles the game logic and changes to game state
    void render(); // handles the drawing of the current game state to the screen

    // used to free resources
    void destroy();

    bool running() {
        return isRunning;
    }

private:
    int frameCount = 0;
    bool isRunning;

    SDL_Window* window;
    SDL_Renderer* renderer;
};