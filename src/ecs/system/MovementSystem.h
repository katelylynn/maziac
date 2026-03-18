//
// Created by kate on 2026-01-21.
//

#ifndef COMP8051_MOVEMENTSYSTEM_H
#define COMP8051_MOVEMENTSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class MovementSystem {
public:
    // unique ptr: smart pointer that manages a dynamically allocated object
    // vector: resizable array
    void update(std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& t = entity->getComponent<Transform>();
                auto& v = entity->getComponent<Velocity>();

                // track previous frame position
                t.oldPosition = t.position;

                Vector2D directionVector = v.direction;
                directionVector.normalize();

                // Vector2D needs an operator function to multiply a float to itself
                Vector2D velocityVector = directionVector * v.speed;

                // alternate option
                // Vector2D velocityVector = v.speed * directionVector;

                t.position += velocityVector * deltaTime;
            }
        }
    }
};

#endif //COMP8051_MOVEMENTSYSTEM_H