//
// Created by kate on 2026-01-14.
//

#include "GameObject.h"

#include "manager/TextureManager.h"

GameObject::GameObject(const char *path, int x, int y) :
xPos(x), yPos(y), texture(TextureManager::load(path)) {

}

GameObject::~GameObject() {
    if (texture) SDL_DestroyTexture(texture);
}

void GameObject::update(float deltaTime) {
    // move game object one pixel on the x and y each frame
    xPos += speed * deltaTime;
    yPos += speed * deltaTime;

    // where we want to crop the texture from, and how much to crop
    // start from top left corner and grab the whole thing
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;

    // where to draw the image
    destRect.x = xPos;
    destRect.y = yPos;

    // what sizes to render
    // keep it the same size as the source
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
}

void GameObject::draw() {
    TextureManager::draw(texture, srcRect, destRect);
}
