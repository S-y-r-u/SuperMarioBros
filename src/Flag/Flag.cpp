#include "Flag/Flag.h"
#include "Constants.h"

Flag::Flag(Vector2 pos)
    : animation_(nullptr),
      pos_(pos),
      velocity_({0, 0}) {}

void Flag::Draw()
{
    Rectangle dest = {pos_.x, pos_.y, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Flag::Set_Pos(Vector2 pos)
{
    pos_ = pos;
}

void Flag::Set_Velocity(Vector2 vel)
{
    velocity_ = vel;
}

Vector2 Flag::Get_Pos() const
{
    return pos_;
}

void Flag::Update_Pos()
{
    pos_.y += velocity_.y * GetFrameTime();
}

Vector2 Flag::Get_Velo() const
{
    return velocity_;
}