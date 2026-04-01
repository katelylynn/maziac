/*
 *  AssetManager.cpp
 *  Handles animation loading behavior.
 */

#include "AssetManager.h"

#include <string>
#include <SDL3/SDL_rect.h>

#include "../ecs/AnimationClip.h"
#include "Component.h"
#include "tinyxml2.h"

std::unordered_map<std::string, Animation> AssetManager::animations;

void AssetManager::loadAnimation(const std::string &clipName, const char *path) {
    Animation animation = loadAnimationFromXML(path);
    animations[clipName] = animation;
}

const Animation& AssetManager::getAnimation(const std::string &clipName) {
    return animations[clipName];
}

Animation AssetManager::loadAnimationFromXML(const char *path) {
    Animation animation;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto* root = doc.FirstChildElement("animations");
    for (auto* clipElement = root->FirstChildElement();
        clipElement;
        clipElement = clipElement->NextSiblingElement()) {

        std::string clipName = clipElement->Name();
        AnimationClip clip;

        for (auto* frameElement = clipElement->FirstChildElement("frame");
            frameElement;
            frameElement = frameElement->NextSiblingElement("frame")) {

            SDL_FRect rect;
            frameElement->QueryFloatAttribute("x", &rect.x);
            frameElement->QueryFloatAttribute("y", &rect.y);
            frameElement->QueryFloatAttribute("w", &rect.w);
            frameElement->QueryFloatAttribute("h", &rect.h);
            clip.frameIndices.push_back(rect);
        }

        animation.clips[clipName] = clip;
    }

    if (!animation.clips.empty()) {
        // set the current clip to the first one in the list
        animation.currentClip = animation.clips.begin()->first;
    }

    return animation;
}


