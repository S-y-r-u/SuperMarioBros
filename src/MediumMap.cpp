#include "MediumMap.h"

MediumMap::MediumMap() {
    MapTexture = LoadTexture("map/Medium.png");
    std::ifstream fi("map/Medium.txt");
    for(int i = 0; i < 15; ++i)
        for(int j = 0; j < 214; ++j)
            fi >> Map[j][i];
}

MediumMap::~MediumMap() {
    UnloadTexture(MapTexture);
}