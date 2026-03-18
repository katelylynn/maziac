//
// Created by kate on 2026-01-14.
//

#include "Map.h"

#include <cmath>

#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>

void Map::load(const char *path, SDL_Texture *ts) {
    tileset = ts;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // parse width and height of map from document
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    // parse terrain data
    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");

    // convert csv to 2D array (vector vector)
    std::string csv = data->GetText();
    std::stringstream ss(csv);

    tileData = std::vector(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;

            // read characters from a ss into val until it hits a comma, or end of stream
            // if any issues, break out of the loop
            if (!std::getline(ss, val, ',')) break;

            tileData[i][j] = std::stoi(val);
        }
    }

    // CHANGE AFTER THIS

    for (auto* itemObjectGroup = layer->NextSiblingElement("objectgroup");
         itemObjectGroup != nullptr;
         itemObjectGroup = itemObjectGroup->NextSiblingElement("objectgroup"))
    {
        // for each object in the object group
        for (auto* obj = itemObjectGroup->FirstChildElement("object");
            obj != nullptr;
            obj = obj->NextSiblingElement("object")) {
            Collider c;
            c.rect.x = obj->FloatAttribute("x") ? obj->FloatAttribute("x") : 0;
            c.rect.y = obj->FloatAttribute("y") ? obj->FloatAttribute("y") : 0;
            c.rect.w = obj->FloatAttribute("width") ? obj->FloatAttribute("width") : 0;
            c.rect.h = obj->FloatAttribute("height") ? obj->FloatAttribute("height") : 0;

            if (std::strcmp(itemObjectGroup->Attribute("name"), "Coin Layer") == 0)
                itemColliders.push_back(c);
            else if (std::strcmp(itemObjectGroup->Attribute("name"), "Collision Layer") == 0)
                colliders.push_back(c);
            }
    }
}

void Map::draw(const Camera &camera) {
    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32; // hardcoded

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int type = tileData[row][col];

            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;

            // convert from world space to screen space
            // move the tiles or map relative to the camera
            dest.x = std::round(worldX - camera.view.x);
            dest.y = std::round(worldY - camera.view.y);

            switch (type) {
                case 1:
                    // dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    // grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    // water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    break;
            }

            TextureManager::draw(tileset, src, dest);
        }
    }
}
