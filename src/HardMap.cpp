#include "HardMap.h"

HardMap::HardMap() {
    MapTexture = LoadTexture("map/Hard.png");
    std::ifstream fi("map/Hard.txt");
    for(int i = 0; i < 15; ++i)
        for(int j = 0; j < 214; ++j)
            fi >> Map[j][i];
}

HardMap::~HardMap() {
    UnloadTexture(MapTexture);
}