#include "Item/Flower.h"

Flower::Flower(Vector2 pos)
    : Item(pos), is_appear(0), before_pos(pos)
{
    rec_ = Item_Sprite::Flower::fire_flower;
}

void Flower::Update_()
{
    Appear_();
}

void Flower::Activate_(Player &player)
{
    player.getFlower();
    is_delete = 1;
}

void Flower::Appear_()
{
    if (is_appear)
        return;
    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos.y - Tile_Size)
    {
        is_appear = 1;
        appear_animation = 0;
        pos_.y = before_pos.y - Tile_Size;
    }
}