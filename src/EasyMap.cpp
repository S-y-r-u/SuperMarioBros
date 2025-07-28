#include "EasyMap.h"

EasyMap::EasyMap()
{
    MapTexture = LoadTexture("map/Easy.png");
    std::ifstream fi("map/Easy.txt");
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 214; ++j)
            fi >> Map[j][i];
    player = new Mario({400, 200});
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