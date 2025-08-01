#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Mario.h"
#include "Item/Item.h"
#include "Item/MushRoom.h"
#include "Item/Star.h"
#include "Item/Spawn_Item.h"
#include "Block/Block.h"
#include "Enemy/Enemy.h"
#include "Enemy/Goomba.h"
#include "Enemy/Latiku.h"
#include "Enemy/PiranhaPlant.h"
#include "Enemy/KoopaTroopa.h"
#include <vector>
#include <algorithm>
#include "PlayerInformation.h"

class Stage
{
private:
    Rectangle source;
    Rectangle dest;

protected:
    Texture MapTexture;
    int Map[214][15];
    Player *player;
    PlayerInformation information;
    Camera2D camera = {0};
    std::vector<KeyboardKey> Keyboard;

    std::vector<Item *> items;
    std::vector<Block *> blocks;
    std::vector<Enemy *> enemies;

public:
    Stage();
    virtual ~Stage();
    void Run();
    void Draw();

    void Check_Player_Vs_Ground();
    void Check_Player_Vs_Block();
    void Check_Player_Vs_Enemy();
    void Check_Enemy_Vs_Ground();
    void Check_Item_Vs_Block();
    void Check_Item_Vs_Ground();
    void Check_Block_Vs_Block();
};