#include "MediumMap.h"

MediumMap::MediumMap(Player_Mode mode, PlayerInformation &info) : Stage(info)
{
    player_mode = mode;
    MapTexture = LoadTexture("map/Medium/Medium.png");
    LoadMapFromFile("map/Medium/Medium.txt");
    Layer[0] = LoadTexture("map/Medium/First_Layer.png");
    Layer[1] = LoadTexture("map/Medium/Second_Layer.png");
    // LoadEnemiesFromFile("map/Medium/Enemy_Medium.txt");
    source = {0, 0, static_cast<float>(MapTexture.width), static_cast<float>(MapTexture.height)};
    dest = {0, 0, static_cast<float>(MapTexture.width * scale_screen), static_cast<float>(MapTexture.height * scale_screen)};
    if (player_mode == Player_Mode::MARIO_PLAYER)
        player = new Mario({400, 200});
    else if (player_mode == Player_Mode::LUIGI_PLAYER)
        player = new Luigi({400, 200});
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    flag_pole = new Flag_Pole({10828, 144});
    flag_castle = new Flag_Castle({11116, 96});
    win_animation = new Win_Animation_Manager(*player, *flag_pole, *flag_castle, information);
}

MediumMap::~MediumMap()
{
    UnloadTexture(MapTexture);
}