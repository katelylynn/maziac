/*
 *  Map.cpp
 *  Provides functionality for loading a map from a tmx file,
 *  generating a procedural map and drawing existing maps.
 */

#include "Map.h"

#include <cmath>

#include "manager/TextureManager.h"
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
        if (std::strcmp(layer->Attribute("name"), "WallLayer") == 0)
            parseLayer(wallData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "EnergyLayer") == 0)
            parseLayer(energyData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "EnergyBarLayer") == 0)
            parseLayer(energyBarData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "GuideLayer") == 0)
            parseLayer(guideData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "WeaponLayer") == 0)
            parseLayer(weaponData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "TreasureLayer") == 0)
            parseLayer(treasureData, layer->FirstChildElement("data"));
        else if (std::strcmp(layer->Attribute("name"), "ExitLayer") == 0)
            parseLayer(exitData, layer->FirstChildElement("data"));

        layer = layer->NextSiblingElement();
    }

    // parse spawn points
    auto* group = mapNode->FirstChildElement("objectgroup");
    while (group != nullptr) {
        if (std::strcmp(group->Attribute("name"), "PlayerSpawn") == 0) {
            playerSpawnpoint.position.x = group->FirstChildElement("object")->FloatAttribute("x");
            playerSpawnpoint.position.y = group->FirstChildElement("object")->FloatAttribute("y");
        }
        else if (std::strcmp(group->Attribute("name"), "EnemySpawn") == 0) {
            for (
                auto* object = group->FirstChildElement("object");
                object != nullptr;
                object = object->NextSiblingElement("object")
            ) {
                Spawnpoint spawnpoint;
                spawnpoint.position.x = object->FloatAttribute("x");
                spawnpoint.position.y = object->FloatAttribute("y");
                enemySpawnpoints.push_back(spawnpoint);
            }
        }

        group = group->NextSiblingElement();
    }
}

void Map::draw() {
    SDL_FRect src{}, dest{};

    // sets the source and dest sizes based on the tmx
    src.w = dest.w = tileWidth;
    src.h = dest.h = tileHeight;

    // for each tile on the map...
    for (int row = 0; row < mapHeight; row++) {
        for (int col = 0; col < mapWidth; col++) {
            // get the position in world space to place the tile
            dest.x = static_cast<float>(col) * dest.w;
            dest.y = static_cast<float>(row) * dest.h;

            // if there's a wall, place a wall tile, otherwise place an ocean tile
            if (wallData[row][col]) {
                src.x = 32;
                src.y = 16;
            } else {
                src.x = 96;
                src.y = 80;
            }

            TextureManager::draw(tileset, src, dest);

            // add the item tile on top
            if (energyData[row][col] == 26) {
                // north
                src.x = 112;
                src.y = 32;
            }
            else if (energyData[row][col] == 16) {
                // east
                src.x = 96;
                src.y = 16;
            }
            else if (energyData[row][col] == 8) {
                // south
                src.x = 112;
                src.y = 0;
            }
            else if (energyData[row][col] == 18) {
                // west
                src.x = 128;
                src.y = 16;
            }
            else if (guideData[row][col] == 50) {
                // north
                src.x = 64;
                src.y = 80;
            }
            else if (guideData[row][col] == 40) {
                // east
                src.x = 48;
                src.y = 64;
            }
            else if (guideData[row][col] == 32) {
                // south
                src.x = 112;
                src.y = 0;
            }
            else if (guideData[row][col] == 32) {
                // west
                src.x = 80;
                src.y = 80;
            }
            else if (weaponData[row][col]) {
                src.x = 16;
                src.y = 0;
            }
            else if (treasureData[row][col]) {
                src.x = 0;
                src.y = 0;
            }
            else if (exitData[row][col]) {
                src.x = 0;
                src.y = 16;
            }

            TextureManager::draw(tileset, src, dest);
        }

        // draw energy bar
        if (energyBarData[row][mapWidth-1]) {
            src.x = 0;
            src.y = 16;
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
