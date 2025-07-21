#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Mario.h"
#include "Item/Item.h"
#include "Item/MushRoom.h"
#include "Item/Star.h"
#include "Block/Block.h"
#include <vector>

class Stage
{
private:
    Rectangle source;
    Rectangle dest;

protected:
    Texture MapTexture;
    int Map[214][15];
    Player *player;
    Camera2D camera = {0};

    std::vector<Item *> items;
    std::vector<Block *> blocks;

public:
    Stage();
    virtual ~Stage();
    void Run();
    void Draw();

    void Check_Item_Vs_Block();
    void Check_Item_Vs_Ground();
};