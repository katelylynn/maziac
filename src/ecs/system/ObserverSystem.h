/*
 *  ObserverSystem.h
 *  Executes behavior for an entity if a value changes.
 */

#ifndef MAZIAC_OBSERVERSYSTEM_H
#define MAZIAC_OBSERVERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class ObserverSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& e : entities) {
            if (e->hasComponent<Observer<float>>()) {
                Observer<float>& observer = e->getComponent<Observer<float>>();

                // check if value has changed
                if (*observer.currValue != observer.oldValue) {
                    // execute callback
                    observer.onValueChange();

                    // set old value to curr value
                    observer.oldValue = *observer.currValue;
                }
            }
        }
    }
};

#endif //MAZIAC_OBSERVERSYSTEM_H