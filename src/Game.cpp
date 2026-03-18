//
// Created by kate on 2026-01-07.
//

#include "Game.h"
#include "Map.h"

#include <iostream>

#include "manager/AssetManager.h"

GameState Game::gameState;
std::function<void(std::string)> Game::onSceneChangeRequest;

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

    // load assets
    AssetManager::loadAnimation("player", "../asset/animations/diver_anim.xml");
    AssetManager::loadAnimation("enemy", "../asset/animations/bird_anim.xml");

    // load scenes
    sceneManager.loadScene(SceneType::MainMenu, "mainmenu", nullptr, width, height);
    sceneManager.loadScene(SceneType::Gameplay, "level1", "../asset/map1.tmx", width, height);
    sceneManager.loadScene(SceneType::Gameplay, "level2", "../asset/map2.tmx", width, height);

    // init game data/state
    gameState.playerHealth = 5;

    // start level 1
    sceneManager.changeSceneDeferred("mainmenu");

    // resolve scene callback
    onSceneChangeRequest = [this](std::string sceneName) {
        // if already at level 2
        if (sceneManager.currentScene->getName() == "level2" && sceneName == "level2") {
            std::cout << "You win!" << std::endl;
            isRunning = false;
        } else if (sceneName == "gameover") {
            std::cout << "You lose!" << std::endl;
            isRunning = false;
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
