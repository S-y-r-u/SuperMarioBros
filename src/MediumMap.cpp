#include "MediumMap.h"

MediumMap::MediumMap(Player_Mode mode, PlayerInformation &info) : Stage(info)
{
    player_mode = mode;
    MapTexture = LoadTexture("map/Medium.png");
    std::ifstream fi;
    fi.open("map/Medium.txt");
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 214; ++j)
            fi >> Map[j][i];
    fi.close();
    LoadMapFromFile("map/Block_Medium.txt");
    if (player_mode == Player_Mode::MARIO_PLAYER)
        player = new Mario({400, 200});
    else if (player_mode == Player_Mode::LUIGI_PLAYER)
        player = new Luigi({400, 200});
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    flag_pole = new Flag_Pole({9530, 144});
    win_animation = new Win_Animation_Manager(9530, *player, *flag_pole, information);
}

MediumMap::~MediumMap()
{
    UnloadTexture(MapTexture);
}