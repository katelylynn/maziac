/*
 *  EventManager.h
 *  Stores listeners and emits events.
 */

#ifndef MAZIAC_EVENTMANAGER_H
#define MAZIAC_EVENTMANAGER_H
#include <functional>

#include "BaseEvent.h"

// observer pattern
class EventManager {
public:
    using Handler = std::function<void(const BaseEvent&)>;

    void emit(const BaseEvent& event) const {
        for (const auto& listener : listeners) {
            listener(event);
        }
    }

    void subscribe(const Handler& callback) {
        listeners.emplace_back(callback);
    }

private:
    std::vector<Handler> listeners;
};

#endif //MAZIAC_EVENTMANAGER_H