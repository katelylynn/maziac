//
// Created by kate on 2026-01-07.
//

#include "Game.h"

#include <iostream>

Game::Game() {}
Game::~Game() {
    destroy();
}

void Game::init(const char *title, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // initialize library
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1) {
        std::cout << "Subsystem initialized..." << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);
        if (window) {
            std::cout << "Window created..." << std::endl;
        }

        // windows will use Direct3D (directx)
        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer) {
            std::cout << "Renderer created..." << std::endl;
        } else {
            std::cout << "Renderer could not be created." << std::endl;
            return;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    // SDL listens to the OS for input events internally and adds them to a queue
    SDL_Event event;

    // check for next event
    // if an event is available, SDL removes it from the queue and store in this event pointer
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT:
            // usually triggered when the user closes the window
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    frameCount++;
    std::cout << frameCount << std::endl;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 100, 100, 0, 10);

    // every frame, SDL clears the renderer with the given draw color
    SDL_RenderClear(renderer);

    //
    // drawing goes here
    //

    // display everything that was just drawn:
    // - draws it in memory first to a back buffer
    // - swaps the back buffer to the screen
    SDL_RenderPresent(renderer);
}

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game destroyed!" << std::endl;
}
