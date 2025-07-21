#include "Item/Star.h"
#include <iostream>

Star::Star(Vector2 pos)
    : Item(pos), direct_(1), is_appear(0), delta_time(0.0f), before_pos(pos)
{
    rec_ = Item_Sprite::Star::invincible_star;
}

void Star::Notify_On_Ground()
{
    if (delta_time != 0.0f)
    {
        delta_time = 0.0f;
        before_pos = pos_;
    }
}

void Star::Notify_Change_Direct() { direct_ = !direct_; }

void Star::Fall_()
{
    if (!is_appear)
        return;
    delta_time += 0.14f;
    float deltaY = -Star_Ini_Velo * delta_time + 0.5 * delta_time * delta_time * Physics::gravity_;
    pos_.y = before_pos.y + deltaY;
}

void Star::Move_()
{
    if (!is_appear)
        return;
    previous_frame_pos = pos_;
    if (direct_)
        pos_.x += Mush_Room_And_Star_Speed;
    else
        pos_.x -= Mush_Room_And_Star_Speed;
    if (pos_.x >= 214 * 48.0f - rec_.width * scale_screen / 2.0f)
    {
        pos_.x = 214 * 48.0f - rec_.width * scale_screen / 2.0f;
        direct_ = !direct_;
    }
    else if (pos_.x <= rec_.width * scale_screen / 2.0f)
    {
        pos_.x = rec_.width * scale_screen / 2.0f;
        direct_ = !direct_;
    }
}

void Star::Appear_()
{
    if (is_appear)
        return;
    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos.y - Tile_Size)
    {
        appear_animation = 0;
        is_appear = 1;
        pos_.y = before_pos.y - Tile_Size;
        before_pos = pos_;
        previous_frame_pos = pos_;
    }
}

void Star::Be_Delete()
{
    if (pos_.y - rec_.height * scale_screen >= Screen_h)
        is_delete = 1;
}

void Star::Update_()
{
    Appear_();
    Move_();
    Fall_();
    Be_Delete();
}

void Star::Activate_(Character &character)
{
    is_delete = 1;
}

Vector2 Star::Get_Previous_Frame_Pos() { return previous_frame_pos; }

bool Star::Get_Direct() const { return direct_; }