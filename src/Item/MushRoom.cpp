#include "Item/MushRoom.h"
#include <iostream>

Mush_Room::Mush_Room(Vector2 pos, State_MushRoom state)
    : Item(pos), state_(state), direct_(1), before_pos(pos_), fall_(0), is_appear(0), delta_time(0.0f)
{
    switch (state_)
    {
    case State_MushRoom::super_:
        rec_ = Item_Sprite::Mushroom::super_mushroom;
        break;
    case State_MushRoom::one_up:
        rec_ = Item_Sprite::Mushroom::one_up_mushroom;
        break;
    case State_MushRoom::posion_:
        rec_ = Item_Sprite::Mushroom::posion_mushroom;
        break;
    default:
        break;
    }
}

void Mush_Room::Notify_Fall()
{
    fall_ = 1;
    before_pos = pos_;
}

void Mush_Room::Notify_On_Ground()
{
    fall_ = 0;
    delta_time = 0.0f;
}

void Mush_Room::Notify_Change_Direct() { direct_ = !direct_; }

void Mush_Room::Fall_()
{
    if (!is_appear || !fall_)
        return;
    delta_time += 0.4f;
    float deltaY = 0.5 * delta_time * delta_time * Physics::gravity_;
    pos_.y = before_pos.y + deltaY;
}

void Mush_Room::Move_()
{
    if (!is_appear || fall_)
        return;
    if (direct_)
        pos_.x += Mush_Room_And_Star_Speed;
    else
        pos_.x -= Mush_Room_And_Star_Speed;
}

void Mush_Room::Appear_()
{
    if (is_appear)
        return;
    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos.y - Tile_Size)
    {
        appear_animation = 0;
        is_appear = 1;
        pos_.y = before_pos.y - Tile_Size;
    }
}

void Mush_Room::Be_Delete()
{
    if (pos_.y - rec_.height * scale_screen >= Screen_h)
        is_delete = 1;
}

void Mush_Room::Update_()
{
    Appear_();
    Move_();
    Fall_();
    Be_Delete();
}

void Mush_Room::Activate_(Character &character)
{
    is_delete = 1;
}