#include "Flag/Flag_Castle.h"

Flag_Castle::Flag_Castle(Vector2 pos)
    : Flag(pos),
      ini_pos(pos)
{
    animation_ = Animation(&Win_Animation::win_animation_, Win_Animation::flag_castle_top::flag_castle_top_, 1 / 8.0f);
}

void Flag_Castle::Update(float dt)
{
    animation_.Update(dt);
    Update_Pos();
    if(Get_Pos().y <= ini_pos.y - Tile_Size)
    {
        Set_Velocity({0, 0});
    }
}