#include "Stage/EasyMap.h"

EasyMap::EasyMap(PlayerInformation &info, Player *&player, Player_Mode &player_mode) : Stage(info, player, player_mode)
{
    MapTexture = LoadTexture("map/Easy/Easy.png");
    map = new MapManagement("map/Easy/Easy.txt");
    LoadBlockFromFile("map/Easy/Block_Easy.txt");
    Layer[0] = LoadTexture("map/Easy/First_Layer.png");
    Layer[1] = LoadTexture("map/Easy/Second_Layer.png");
    source = {0, 0, static_cast<float>(MapTexture.width), static_cast<float>(MapTexture.height)};
    dest = {0, 0, static_cast<float>(MapTexture.width * scale_screen), static_cast<float>(MapTexture.height * scale_screen)};
    LoadEnemiesFromFile("map/Easy/Enemy_Easy.txt");
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    win_animation = new Win_Animation_Climb_Flag(player, {9530, 144}, {9818, 384}, information);
}

EasyMap::~EasyMap()
{
    UnloadTexture(MapTexture);
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(Layer[i]);
    }
}