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
    camera.rotation = 0;
    camera.zoom = 1;
    enemies.push_back(new Goomba({100, 100}, {100.0f, 0}, 500.0f));
    enemies.push_back(new Latiku({200, 100}, 40.f, player, &enemies));
    enemies.push_back(new PiranhaPlant({500, 400}, player));
    enemies.push_back(new KoopaTroopa({300, 200}, 1));
    enemies.push_back(new KoopaTroopa({600, 200}, 0));
}

EasyMap::~EasyMap()
{
    delete player;
    UnloadTexture(MapTexture);
}