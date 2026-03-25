/*
 *  main.cpp
 *  Inits the game, loops through the game loop functions, and limits the frame rate.
 */

#include "Game.h"

// global variable
// referenced by texture manager
Game* game = nullptr;

int main() {
    const int FPS = 60;
    const int desiredFrameTime = 1000 / FPS; // 16ms per frame

    Uint64 ticks = SDL_GetTicks(); // time of SDL initialization
    Uint64 currentTicks; // time of SDL init + how long the game has been running

    float deltaTime = 0.0f; // real time elapsed since the last frame

    game = new Game();
    game->init("MAZIAC");

    // game loop
    while (game->running()) {
        currentTicks = SDL_GetTicks(); // update how long game has been running
        deltaTime = (currentTicks - ticks) / 1000.0f; // get current frame time
        ticks = currentTicks;

        // run game loop functions
        game->handleEvents();
        game->update(deltaTime);
        game->render();

        // elapsed time in ms it took the current frame
        int actualFrameTime = SDL_GetTicks() - ticks;

        // frame limiter
        // keeps the game running at the desired frame rate
        // if the actual frame took less time than the desired frame, delay the difference
        if (desiredFrameTime > actualFrameTime) {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }
    }

    // must be manually cleaned up from the heap
    delete game;

    return 0;
}