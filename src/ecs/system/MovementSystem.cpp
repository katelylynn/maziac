/*
 *  MovementSystem.cpp
 *  Handles discrete tile movement using Translation, Transform and Velocity.
 */

#include "MovementSystem.h"

#include "World.h"

// unique ptr: smart pointer that manages a dynamically allocated object
// vector: resizable array
void MovementSystem::update(
    std::vector<std::unique_ptr<Entity>>& entities,
    float deltaTime,
    World* world
) {
    for (auto& entity : entities) {
        if (
            entity->hasComponent<Translation>() &&
            entity->hasComponent<Transform>() &&
            entity->hasComponent<Velocity>()
        ) {
            auto& translation = entity->getComponent<Translation>();
            auto& transform = entity->getComponent<Transform>();
            auto& velocity = entity->getComponent<Velocity>();

            // if translation is not initialized, initialize it
            if (translation.startPosition == Vector2D{-1.0f, -1.0f} ||
                translation.endPosition == Vector2D{-1.0f,-1.0f}) {
                translation.startPosition = transform.position;
                translation.endPosition = transform.position;
            }

            if (
                // if the entitiy's current position is at the end position...
                transform.position.approxEquals(translation.endPosition, 1.0f)
            ) {
                // snap perfectly to that position
                transform.position = translation.endPosition;

                // start a new move if a key is being pressed and entity isn't currently colliding with anything
                if (velocity.direction.x != 0 || velocity.direction.y != 0) {
                    // set the new start position of the translation
                    translation.startPosition = translation.endPosition;

                    // set the new destination
                    translation.endPosition.x += world->getMap().tileWidth * velocity.direction.x;
                    translation.endPosition.y += world->getMap().tileHeight * velocity.direction.y;
                }
            }
            // else need to complete the current movement
            else {
                transform.position += (translation.endPosition - transform.position).normalize() * deltaTime * velocity.speed;
            }
        }
    }
}