//
// Created by kate on 2026-02-25.
//

#ifndef COMP8051_ASSETMANAGER_H
#define COMP8051_ASSETMANAGER_H
#include <unordered_map>

#include "ecs/Component.h"

class AssetManager {
    static std::unordered_map<std::string, Animation> animations;
    static Animation loadAnimationFromXML(const char *path);
public:
    static void loadAnimation(const std::string& clipName, const char *path);
    static const Animation& getAnimation(const std::string& clipName);
};

#endif //COMP8051_ASSETMANAGER_H