/*
 *  Game.cpp
 *  Starts the SDL window, loads scenes/assets and runs the game loop functions.
 */

#include "Game.h"
#include "SDL3_image/SDL_image.h"

#include <iostream>

#include "manager/AssetManager.h"

std::function<void(std::string)> Game::onSceneChangeRequest;

Game::Game() : event() {}
Game::~Game() { destroy(); }

void Game::init(const char *title) {
    // screen
    int width, height;

    // initialize library
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1) {
        std::cout << "Subsystem initialized..." << std::endl;
        window = SDL_CreateWindow(title, 0, 0, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
        if (window) {
            std::cout << "Window created..." << std::endl;
        }

        // set the screen width and height
        SDL_GetWindowSize(window, &width, &height);

        // windows will use Direct3D (directx)
        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer) {
            std::cout << "Renderer created..." << std::endl;
        } else {
            std::cout << "Renderer could not be created." << std::endl;
            return;
        }

        // set the virtual size
        SDL_SetRenderLogicalPresentation(
            renderer,
            496, 320, // hardcoded for now
            SDL_LOGICAL_PRESENTATION_STRETCH
        );

        isRunning = true;
    } else {
        isRunning = false;
        return;
    }

    // load animations
    AssetManager::loadAnimation("character", "../asset/animations/character_anim.xml");

    // load scenes
    // sceneManager.loadScene(SceneType::MainMenu, "mainmenu", nullptr, width, height);
    sceneManager.loadScene(SceneType::Gameplay, "maze", "../asset/map/handmade_map.tmx", width, height);

    // load the starting level
    sceneManager.changeSceneDeferred("maze");

    // resolve scene callback
    onSceneChangeRequest = [this](std::string sceneName) {
        // if completed maze...
        if (sceneName == "win") {
            std::cout << "You win!" << std::endl;
            isRunning = false;
        // if died to enemy...
        } else if (sceneName == "lose") {
            std::cout << "You lose!" << std::endl;
            isRunning = false;
        // change to given scene...
        } else {
            sceneManager.changeSceneDeferred(sceneName);
        }
    };
}

void Game::handleEvents() {
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

void Game::update(float deltaTime) {
    sceneManager.update(deltaTime, event);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // every frame, SDL clears the renderer with the given draw color
    SDL_RenderClear(renderer);

    sceneManager.render();

    // display everything that was just drawn:
    // - draws it in memory first to a back buffer
    // - swaps the back buffer to the screen
    SDL_RenderPresent(renderer);
}

void Game::destroy() {
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game destroyed!" << std::endl;
}
