#include "EasyMap.h"

EasyMap::EasyMap()
{
    MapTexture = LoadTexture("map/Easy.png");
    std::ifstream fi("map/Easy.txt");
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 214; ++j)
            fi >> Map[j][i];
    player = new Mario({400, 200});
    camera.target = {0, 0};
    camera.offset = {0, 0};
    Spawn_Item::Mush_Room_Spawner(items, {600, 200}, State_MushRoom::super_);
    Spawn_Item::Flower_Spawner(items, {500, 400});
    camera.target = player->getPosition();
    camera.offset = {Screen_w / 2.0, Screen_h / 2.0};
    camera.rotation = 0;
    camera.zoom = 1;
}

EasyMap::~EasyMap()
{
    delete player;
    UnloadTexture(MapTexture);
}