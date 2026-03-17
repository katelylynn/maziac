#include <iostream>

#include "Game.h"

// global variable
Game* game = nullptr;

int main() {
    const int FPS = 60;
    const int desiredFrameTime = 1000 / FPS; // 16ms per frame

    Uint64 ticks;
    int actualFrameTime;

    game = new Game();
    game->init("maziac", 800, 600, false);

    // GAME LOOP
    while (game->running()) {
        ticks = SDL_GetTicks(); // time in ms

        // run the game loop functions
        game->handleEvents();
        game->update();
        game->render();

        // elapsed time in ms it took the current frame
        actualFrameTime = SDL_GetTicks() - ticks;

        // frame limiter
        // keeps the game running at the desired frame rate
        // if the actual frame took less time than the desired frame, delay the difference
        if (desiredFrameTime > actualFrameTime) {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }
    }

    delete game; // manual clean up from the heap

    return 0;
}