/*
 *  CollisionSystem.cpp
 *  Updates collider positions, checks for collisions and emits events
 */

#include "CollisionSystem.h"

#include "Collision.h"
#include "World.h"

void CollisionSystem::update(World &world) {
    // get a list of entities that have colliders and transforms
    const std::vector<Entity*> collidables = queryCollidables(world.getEntities());

    // update all collider positions first
    for (auto entity : collidables) {
        auto& t = entity->getComponent<Transform>();
        auto& c = entity->getComponent<Collider>();
        c.rect.x = t.position.x + c.offset.x;
        c.rect.y = t.position.y + c.offset.y;
    }

    std::set<CollisionKey> currentCollisions;

    // for each collidable...
    for (size_t i = 0; i < collidables.size(); i++) {
        auto entityA = collidables[i];
        auto& colliderA = entityA->getComponent<Collider>();

        // check for collider collision against other collidables
        for (size_t j = i + 1; j < collidables.size(); j++) {
            auto entityB = collidables[j];
            auto& colliderB = entityB->getComponent<Collider>();

            if (Collision::AABB(colliderA, colliderB)) {
                CollisionKey key = makeKey(entityA, entityB);
                currentCollisions.insert(key);

                // prevents enter from being emitted if already in active collisions
                if (!activeCollisions.contains(key))
                    world.getEventManager().emit(CollisionEvent{entityA, entityB, CollisionState::Enter});

                world.getEventManager().emit(CollisionEvent{entityA, entityB, CollisionState::Stay});
            }
        }
    }

    // for each active collision
    for (auto& key : activeCollisions) {
        // if the previously "active" collisions are no longer active
        if (!currentCollisions.contains(key)) {
            // emit exit event
            world.getEventManager().emit(CollisionEvent{key.first, key.second, CollisionState::Exit});
        }
    }

    // update active collisions with current collisions
    activeCollisions = std::move(currentCollisions);
}

// grabs all the collidables
std::vector<Entity*> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities) {
    std::vector<Entity*> collidables;

    for (auto& entity : entities) {
        if (entity->hasComponent<Transform>() && entity->hasComponent<Collider>()) {
            collidables.push_back(entity.get());
        }
    }

    return collidables;
}
