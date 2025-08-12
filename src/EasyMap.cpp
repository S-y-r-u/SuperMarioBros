#include "EasyMap.h"

EasyMap::EasyMap(Player_Mode mode, PlayerInformation &info) : Stage(info)
{
    player_mode = mode;
    MapTexture = LoadTexture("map/Easy/Easy.png");
    LoadMapFromFile("map/Easy/Easy.txt");
    LoadBlockFromFile("map/Easy/Block_Easy.txt");
    if (player_mode == Player_Mode::MARIO_PLAYER)
        player = new Mario({400, 200});
    else if (player_mode == Player_Mode::LUIGI_PLAYER)
        player = new Luigi({400, 200});
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    blocks.push_back(new Block({600, 400}, 1, "rotating_bar", "unbreakable"));
    LoadEnemiesFromFile("map/Easy/Enemy_Easy.txt");
    flag_pole = new Flag_Pole({9530, 144});
    win_animation = new Win_Animation_Manager(9530, *player, *flag_pole, information);
}

EasyMap::~EasyMap()
{
    UnloadTexture(MapTexture);
}