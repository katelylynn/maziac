/*
 *  EnemyWanderSystem.h
 */

#ifndef MAZIAC_ENEMYWANDERSYSTEM_H
#define MAZIAC_ENEMYWANDERSYSTEM_H
#include <memory>
#include <random>
#include <vector>

#include "Entity.h"
#include "Map.h"

class EnemyWanderSystem {
private:
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dist{0, 3};
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float deltaTime, Map& map) {
        for (auto& entity : entities) {
            if (
                entity->hasComponent<Enemy>() &&
                entity->hasComponent<Transform>() &&
                entity->hasComponent<Velocity>()
            ) {
                auto& enemy = entity->getComponent<Enemy>();
                auto& transform = entity->getComponent<Transform>();
                auto& velocity = entity->getComponent<Velocity>();

                enemy.currentWait -= deltaTime * 1000.0f;

                velocity.direction.x = 0;
                velocity.direction.y = 0;
                if (enemy.currentWait > 0) continue;

                int direction = dist(gen);
                int row = transform.position.y / map.tileHeight;
                int col = transform.position.x / map.tileWidth;

                switch (direction) {
                    case 0: // north
                        if (map.wallData[row - 1.0f][col] != 0.0f) return;
                        if (std::abs((row - 1.0f) - enemy.startingPosition.y / map.tileHeight) > enemy.wanderRange) return;
                        velocity.direction.x = 0;
                        velocity.direction.y = -1;
                        break;
                    case 1: // east
                        if (map.wallData[row][col + 1.0f] != 0.0f) return;
                        if (std::abs((col + 1.0f) - enemy.startingPosition.x / map.tileWidth) > enemy.wanderRange) return;
                        velocity.direction.x = 1;
                        velocity.direction.y = 0;
                        break;
                    case 2: // south
                        if (map.wallData[row + 1.0f][col] != 0.0f) return;
                        if (std::abs((row + 1.0f) - enemy.startingPosition.y / map.tileHeight) > enemy.wanderRange) return;
                        velocity.direction.x = 0;
                        velocity.direction.y = 1;
                        break;
                    case 3: // west
                        if (map.wallData[row][col - 1.0f] != 0.0f) return;
                        if (std::abs((col - 1.0f) - enemy.startingPosition.x / map.tileWidth) > enemy.wanderRange) return;
                        velocity.direction.x = -1;
                        velocity.direction.y = 0;
                        break;
                    default:
                        velocity.direction.x = 0;
                        velocity.direction.y = 0;
                        break;
                }

                enemy.currentWait = dist(gen) / 3.0f * enemy.maxWait;
            }
        }
    }
};

#endif //MAZIAC_ENEMYWANDERSYSTEM_H