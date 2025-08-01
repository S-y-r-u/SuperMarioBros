#include "EasyMap.h"

EasyMap::EasyMap()
{
    MapTexture = LoadTexture("map/Easy.png");
    std::ifstream fi;
    fi.open("map/Easy.txt");
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 214; ++j)
            fi >> Map[j][i];
    fi.close();
    fi.open("map/Block_Easy.txt");
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
    player = new Mario({400, 200});
    information.SetWorld("EASY");
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0;
    camera.zoom = 1;
    enemies.push_back(new Goomba({100, 100}, {100.0f, 0}, 500.0f));
    // enemies.push_back(new Latiku({200, 100}, 40.f, player, &enemies));
    enemies.push_back(new PiranhaPlant({500, 400}, player));
    enemies.push_back(new KoopaTroopa({1000, 200}, 1));
    enemies.push_back(new KoopaTroopa({600, 400}, 0));
}

EasyMap::~EasyMap()
{
    delete player;
    UnloadTexture(MapTexture);
}