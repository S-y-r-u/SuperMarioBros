#include "GameManager/Win_Animation.h"

Win_Animation_Manager::Win_Animation_Manager(Player &player, Flag_Pole &flag_pole, Flag_Castle &flag_castle, PlayerInformation &player_info)
    : player_(player),
      flag_pole_(flag_pole),
      flag_castle_(flag_castle),
      player_info_(player_info),
      Flag_Pos_X(flag_pole.Get_Pos().x),
      Castle_Door_X(flag_pole.Get_Pos().x + 288.0f),
      preparing_to_castle(false),
      go_to_castle(false),
      is_climbing(false),
      frame_timer(0.0f),
      is_pose(false),
      is_fade_out(false),
      flag_raise(false),
      player_disappear(false) {}

int Win_Animation_Manager::Calculate_Bonus_Points()
{
    float heightRange = Flag_Bottom_y - Flag_Top_y;
    float relativePos = (Flag_Bottom_y - player_.getPosition().y + player_.get_draw_rec().height) / heightRange; // 1.0 = cao nhất

    if (relativePos > 0.9f)
        return 5000;
    else if (relativePos > 0.7f)
        return 2000;
    else if (relativePos > 0.5f)
        return 800;
    else if (relativePos > 0.3f)
        return 400;
    else
        return 100;
}

bool Win_Animation_Manager::Check_Win_Animation()
{
    if (player_.getPosition().x + player_.get_draw_rec().width / 2.0f >= Flag_Pos_X)
    {
        Enter_Win_Animation();
        return true;
    }
    return false;
}

void Win_Animation_Manager::Enter_Win_Animation()
{
    bonus_points = Calculate_Bonus_Points();
    Score_Manager::GetInstance().AddScore({Flag_Pos_X + 20.0f, player_.getPosition().y - player_.get_draw_rec().height}, bonus_points);
    player_info_.UpdateScore(bonus_points);
    flag_pole_.Set_Velocity({0, Slide_Speed});
    player_.Climb(Slide_Speed);
    player_.Set_Pos({Flag_Pos_X - player_.get_draw_rec().width / 2.0f, player_.getPosition().y});
    mario_base_y = Flag_Bottom_y + Tile_Size - 10.0f;
    is_climbing = true;
    player_info_.Game_Won();
}

void Win_Animation_Manager::Update(float dt)
{
    if (is_climbing)
        Climb_Flag_Pole();
    if (preparing_to_castle)
        Prepare_To_Castle();
    if (go_to_castle)
        Go_To_Castle();
    if (is_pose)
        Pose();
    if (is_fade_out)
        Fade_Out();
    Raise_Flag();
}

void Win_Animation_Manager::Climb_Flag_Pole()
{
    if (player_.getPosition().y >= mario_base_y)
    {
        player_.End_Climb();
    }
    if (flag_pole_.Get_Pos().y >= Flag_Bottom_y)
    {
        is_climbing = false;
        flag_pole_.Set_Velocity({0, 0});
        preparing_to_castle = true;
    }
}

void Win_Animation_Manager::Prepare_To_Castle()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        go_to_castle = true;
        preparing_to_castle = false;
        frame_timer = 0.0f;
        player_.Set_isGround(true);
        player_.Jump();
        player_.Cut_Jump();
        player_.Cut_Jump();
        return;
    }
    player_.Set_Pos({Flag_Pos_X + player_.get_draw_rec().width / 2.0f, mario_base_y});
    player_.Set_Is_Facing_Right(false);
}

void Win_Animation_Manager::Go_To_Castle()
{
    player_.MoveRight();
    if (player_.getPosition().x - player_.get_draw_rec().width / 2.0f >= Castle_Door_X)
    {
        go_to_castle = false;
        is_pose = true;
        frame_timer = 0.0f;
        player_.Pose(Cool_Down_Time);
    }
}

void Win_Animation_Manager::Pose()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        is_pose = false;
        is_fade_out = true;
        frame_timer = 0.0f;
        player_.Fade_Out(Cool_Down_Time);
    }
}

void Win_Animation_Manager::Fade_Out()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        is_fade_out = false;
        frame_timer = 0.0f;
        player_info_.Up_Score();
        player_disappear = true;
    }
}

bool Win_Animation_Manager::End_Animation()
{
    if (flag_raise && flag_castle_.Get_Velo().y == 0.0f)
        return true;
    return false;
}

void Win_Animation_Manager::Raise_Flag()
{
    if (player_info_.GetTime() < 0)
    {
        player_info_.Set_Time_To_0();
        flag_raise = true;
        flag_castle_.Set_Velocity({0, -Slide_Speed / 2.0f});
    }
}

bool Win_Animation_Manager::Player_Disappear()
{
    return player_disappear;
}
