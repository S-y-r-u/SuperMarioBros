#include "Item/Spawn_Item.h"

void Spawn_Item::Coin_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Coin(pos));
}

void Spawn_Item::Star_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Star(pos));
}

void Spawn_Item::Hidden_Coin_Spawner(std::vector<Item *> &items, Vector2 pos, Player &player, PlayerInformation &info)
{
    items.push_back(new HiddenCoin(pos));
    items.back()->Activate_(player, info);
}

void Spawn_Item::Flower_Spawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Flower(pos));
}

void Spawn_Item::Mush_Room_Spawner(std::vector<Item *> &items, Vector2 pos, State_MushRoom state)
{
    items.push_back(new Mush_Room(pos, state));
}

void Spawn_Item::Item_Spawn(const std::string &type_item, std::vector<Item *> &items, Vector2 pos, Player &player, PlayerInformation &info)
{
    if (type_item == "flower" || type_item == "super_mushroom")
    {
        if (player.get_form() == PlayerForm::Small)
            Mush_Room_Spawner(items, pos, State_MushRoom::super_);
        else
            Flower_Spawner(items, pos);
        SoundManager::GetInstance().PlaySoundEffect("powerup_appears");
    }
    if (type_item == "hidden_coin")
    {
        SoundManager::GetInstance().PlaySoundEffect("coin");
        Hidden_Coin_Spawner(items, pos, player, info);
    }
    if (type_item == "one_up_mushroom")
    {
        SoundManager::GetInstance().PlaySoundEffect("1-up");
        Mush_Room_Spawner(items, pos, State_MushRoom::one_up);
    }
    if (type_item == "posion_mushroom")
    {
        SoundManager::GetInstance().PlaySoundEffect("powerup_appears");
        Mush_Room_Spawner(items, pos, State_MushRoom::posion_);
    }
    if (type_item == "star")
    {
        SoundManager::GetInstance().PlaySoundEffect("powerup_appears");
        Star_Spawner(items, pos);
    }
}

