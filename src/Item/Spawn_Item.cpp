#include "Item/Spawn_Item.h"

void Spawn_Item::Coin_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Coin(pos));
}

void Spawn_Item::Star_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Star(pos));
}

void Spawn_Item::Hidden_Coin_Spawner(std::vector<Item *> &items, Vector2 pos, Character &character)
{
    items.push_back(new HiddenCoin(pos));
    items.back()->Activate_(character);
}

void Spawn_Item::Flower_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Flower(pos));
}

void Spawn_Item::Mush_Room_Spawner(std::vector<Item *> &items, Vector2 pos, State_MushRoom state)
{
    items.push_back(new Mush_Room(pos, state));
}

void Spawn_Item::Item_Spawn(const std::string &type_item, std::vector<Item *> &items, Vector2 pos, Character &character)
{
    if (type_item == "star")
        Star_Spawner(items, pos);
    if (type_item == "hidden_coin")
        Hidden_Coin_Spawner(items, pos, character);
    if (type_item == "one_up_mushroom")
        Mush_Room_Spawner(items, pos, State_MushRoom::one_up);
    if (type_item == "posion_mushroom")
        Mush_Room_Spawner(items, pos, State_MushRoom::posion_);
    if (type_item == "super_mushroom")
        Mush_Room_Spawner(items, pos, State_MushRoom::super_);
    if (type_item == "flower")
        Flower_Spawner(items, pos);
}