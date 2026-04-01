/*
 *  GameObject.h
 *  Defines the game object's position and texture.
 */

#ifndef MAZIAC_GAMEOBJECT_H
#define MAZIAC_GAMEOBJECT_H

#include "Game.h" // so we have a reference to SDL

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

#endif //MAZIAC_GAMEOBJECT_H