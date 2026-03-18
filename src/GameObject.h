//
// Created by kate on 2026-01-14.
//

#ifndef COMP8051_GAMEOBJECT_H
#define COMP8051_GAMEOBJECT_H

#include "Game.h" // bc we need SDL

class GameObject {
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update(float deltaTime);
    void draw();
private:
    int xPos{}, yPos{};

    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, destRect{};

    int speed = 100;
};

#endif //COMP8051_GAMEOBJECT_H