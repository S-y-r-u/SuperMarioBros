#include "EasyMap.h"

EasyMap::EasyMap(Player_Mode mode, PlayerInformation &info) : Stage(info)
{
    player_mode = mode;
    MapTexture = LoadTexture("map/Easy/Easy.png");
    std::ifstream fi;
    fi.open("map/Easy/Easy.txt");
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 214; ++j)
            fi >> Map[j][i];
    fi.close();
    fi.open("map/Easy/Block_Easy.txt");
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 214; ++j)
        {
            int var;
            fi >> var;
            Vector2 pos = {(j + 0.5) * Tile_Size, (i + 1) * Tile_Size};
            if (var < 100)
                continue;
            int type_block = var / 100;
            int type_item = (var % 100) / 10;
            int item_cnt = var % 10;
            if (type_block == 1 && type_item == 0 && item_cnt == 0)
                blocks.push_back(new Block(pos, 0, "", "question"));
            else if (type_block == 1 && type_item == 0)
                blocks.push_back(new Block(pos, item_cnt, "super_mushroom", "question"));
            else if (type_block == 1 && type_item == 1)
                blocks.push_back(new Block(pos, item_cnt, "one_up_mushroom", "question"));
            else if (type_block == 1 && type_item == 2)
                blocks.push_back(new Block(pos, item_cnt, "posion_mushroom", "question"));
            else if (type_block == 1 && type_item == 3)
                blocks.push_back(new Block(pos, item_cnt, "hidden_coin", "question"));
            else if (type_block == 1 && type_item == 4)
                blocks.push_back(new Block(pos, item_cnt, "flower", "question"));
            else if (type_block == 1 && type_item == 5)
                blocks.push_back(new Block(pos, item_cnt, "star", "question"));
            else if (type_block == 2 && type_item == 0 && item_cnt == 0)
                blocks.push_back(new Block(pos, 0, "", "normal"));
            else if (type_block == 2 && type_item == 0)
                blocks.push_back(new Block(pos, item_cnt, "super_mushroom", "normal"));
            else if (type_block == 2 && type_item == 1)
                blocks.push_back(new Block(pos, item_cnt, "one_up_mushroom", "normal"));
            else if (type_block == 2 && type_item == 2)
                blocks.push_back(new Block(pos, item_cnt, "posion_mushroom", "normal"));
            else if (type_block == 2 && type_item == 3)
                blocks.push_back(new Block(pos, item_cnt, "hidden_coin", "normal"));
            else if (type_block == 2 && type_item == 4)
                blocks.push_back(new Block(pos, item_cnt, "flower", "normal"));
            else if (type_block == 2 && type_item == 5)
                blocks.push_back(new Block(pos, item_cnt, "star", "normal"));
        }
    }
    fi.close();
    if (player_mode == Player_Mode::MARIO_PLAYER)
        player = new Mario({400, 200});
    else if (player_mode == Player_Mode::LUIGI_PLAYER)
        player = new Luigi({400, 200});
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    LoadEnemiesFromFile("map/Easy/Enemy_Easy.txt");
}

EasyMap::~EasyMap()
{
    UnloadTexture(MapTexture);
}