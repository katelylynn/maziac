/*
 *  Map.cpp
 *  Provides functionality for loading a map from a tmx file,
 *  generating a procedural map and drawing existing maps.
 */

#include "Map.h"

#include <cmath>
#include <iostream>

#include "TextureManager.h"
#include <sstream>
#include <tinyxml2.h>

void Map::load(const char *path, SDL_Texture *ts) {
    tileset = ts;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);
    auto* mapNode = doc.FirstChildElement("map");

    // parse map width/height and tile width/height from document
    mapWidth = mapNode->IntAttribute("width");
    mapHeight = mapNode->IntAttribute("height");
    tileWidth = mapNode->IntAttribute("tilewidth");
    tileHeight = mapNode->IntAttribute("tileheight");

    // parse each layer
    auto* layer = mapNode->FirstChildElement("layer");
    while (layer != nullptr) {
        if (std::strcmp(layer->Attribute("name"), "OceanLayer") == 0)
            parseLayer(oceanData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "WallLayer") == 0)
            parseLayer(wallData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "EnergyLayer") == 0)
            parseLayer(energyData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "GuideLayer") == 0)
            parseLayer(guideData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "WeaponLayer") == 0)
            parseLayer(weaponData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "TreasureLayer") == 0)
            parseLayer(treasureData, layer->FirstChildElement("data"));

        layer = layer->NextSiblingElement();
    }
}

void Map::draw(const Camera &camera) {
    SDL_FRect src{}, dest{};

    // sets the source and dest sizes based on the tmx
    src.w = dest.w = tileWidth;
    src.h = dest.h = tileHeight;

    // for each tile on the map...
    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            // get the position in world space to place the tile
            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;

            // convert from world space to screen space
            // move the tiles or map relative to the camera
            dest.x = std::round(worldX - camera.view.x);
            dest.y = std::round(worldY - camera.view.y);

            // if there's a wall, place a wall tile, otherwise place an ocean tile
            if (wallData[row][col]) {
                src.x = 32;
                src.y = 16;
            } else {
                src.x = 96;
                src.y = 80;
            }

            TextureManager::draw(tileset, src, dest);
        }
    }
}

void Map::parseLayer(std::vector<std::vector<int>> &layer, auto* data) {
    // convert csv to 2D array (vector vector)
    std::string csv = data->GetText();
    std::stringstream ss(csv);

    // init layer to new vector
    layer = std::vector(mapHeight, std::vector<int>(mapWidth));

    // iterate through 2D array and store into layer variable
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            std::string val;

            // read characters from a ss into val until it hits a comma, or end of stream
            // if any issues, break out of the loop
            if (!std::getline(ss, val, ',')) break;

            layer[i][j] = std::stoi(val);
        }
    }
}
