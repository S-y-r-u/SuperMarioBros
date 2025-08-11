#include "Flag/Flag_Pole.h"

Flag_Pole::Flag_Pole(Vector2 pos)
    : Flag(pos)
{
    animation_ = Animation(&Win_Animation::win_animation_, Win_Animation::flag_pole::flag_pole_, 1 / 8.0f);
}

void Flag_Pole::Update(float deltaTime)
{
    animation_.Update(deltaTime);
    Update_Pos();
}