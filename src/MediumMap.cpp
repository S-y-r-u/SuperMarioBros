#include "MediumMap.h"

MediumMap::MediumMap(PlayerInformation &info, Player *&player) : Stage(info, player)
{
    MapTexture = LoadTexture("map/Medium/Medium.png");
    LoadMapFromFile("map/Medium/Medium.txt");
    Layer[0] = LoadTexture("map/Medium/First_Layer.png");
    Layer[1] = LoadTexture("map/Medium/Second_Layer.png");
    LoadEnemiesFromFile("map/Medium/Enemy_Medium.txt");
    source = {0, 0, static_cast<float>(MapTexture.width), static_cast<float>(MapTexture.height)};
    dest = {0, 0, static_cast<float>(MapTexture.width * scale_screen), static_cast<float>(MapTexture.height * scale_screen)};
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    win_animation = new Win_Animation_Climb_Flag(player, {10828, 144}, {11116, 96}, information);
}

MediumMap::~MediumMap()
{
    UnloadTexture(MapTexture);
}