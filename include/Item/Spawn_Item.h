#pragma once
#include "Item.h"
#include "Coin.h"
#include "Flower.h"
#include "HiddenCoin.h"
#include "MushRoom.h"
#include "Star.h"

class Spawn_Item
{
public:
    static void Coin_Spawner(std::vector<Item *> &items, Vector2 pos);
    static void Star_Spawner(std::vector<Item *> &items, Vector2 pos);
    static void Hidden_Coin_Spawner(std::vector<Item *> &items, Vector2 pos, Player &player, PlayerInformation &info);
    static void Flower_Spawner(std::vector<Item *> &items, Vector2 pos);
    static void Mush_Room_Spawner(std::vector<Item *> &items, Vector2 pos, State_MushRoom state);
    static void Item_Spawn(const std::string &type_item, std::vector<Item *> &items, Vector2 pos, Player &player, PlayerInformation &info);
};
