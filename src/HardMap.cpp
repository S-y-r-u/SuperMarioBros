#include "HardMap.h"

HardMap::HardMap(PlayerInformation &info, Player &player) : Stage(info, player)
{
    MapTexture = LoadTexture("map/Hard/Hard.png");
    LoadMapFromFile("map/Hard/Hard.txt");
    Layer[0] = LoadTexture("map/Hard/First_Layer.png");
    source = {0, 0, static_cast<float>(MapTexture.width), static_cast<float>(MapTexture.height)};
    dest = {0, 0, static_cast<float>(MapTexture.width * scale_screen), static_cast<float>(MapTexture.height * scale_screen)};

    win_animation = new Win_Animation_Save_Prince({6840, 480}, {7440, 624}, info, &player);
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
}

HardMap::~HardMap()
{
    UnloadTexture(MapTexture);
}