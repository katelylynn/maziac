/*
 *  AnimationSystem.h
 *  Defines the state, checker and playback systems.
 *  State system: decides which clip to use.
 *  Checker system: checks if the animation has been switched.
 *  Playback system: advances the animation.
 */

#ifndef MAZIAC_ANIMATIONSYSTEM_H
#define MAZIAC_ANIMATIONSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class AnimationSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Animation>() && entity->hasComponent<Velocity>()) {
                auto& animation = entity->getComponent<Animation>();
                auto& velocity = entity->getComponent<Velocity>();

                // state system
                std::string newClip;

                if (velocity.direction.x > 0.0f)
                    newClip = "walk_right";
                else if (velocity.direction.x < 0.0f)
                    newClip = "walk_left";
                else if (velocity.direction.y > 0.0f)
                    newClip = "walk_down";
                else if (velocity.direction.y < 0.0f)
                    newClip = "walk_up";
                else
                    newClip = "idle_left";

                // checker system
                if (
                    animation.clips.contains(newClip) && // clip exists
                    newClip != animation.currentClip // not the currently playing one
                ) {
                    animation.currentClip = newClip;
                    animation.time = 0.0f;
                    animation.currentFrame = 0; // reset frame index to zero
                }

                // playback system
                float animationFrameSpeed = animation.speed; // how long each 'animation frame' should last
                auto clip = animation.clips[animation.currentClip]; // retrieve the frame data from the current clip
                // advance time
                animation.time += deltaTime; // every 'game loop frame', we add to the accumulated anim time
                // once enough time has passed
                if (animation.time >= animationFrameSpeed) {
                    animation.time -= animationFrameSpeed; // subtract animationFrameSpeed so extra time isn't lost
                    std::size_t totalAnimationFrames = clip.frameIndices.size();
                    // advance to the next frame (current + 1)
                    // wrap around % so it loops when reaching the end of the clip
                    animation.currentFrame = (animation.currentFrame + 1) % totalAnimationFrames;
                }
            }
        }
    }
};

#endif //MAZIAC_ANIMATIONSYSTEM_H