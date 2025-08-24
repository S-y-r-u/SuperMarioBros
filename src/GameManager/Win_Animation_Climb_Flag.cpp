#include "GameManager/Win_Animation_Climb_Flag.h"

Win_Animation_Climb_Flag::Win_Animation_Climb_Flag(Player *&player, Vector2 flag_pole, Vector2 flag_castle, PlayerInformation &player_info)
    : player_(player),
      flag_pole_(new Flag_Pole(flag_pole)),
      flag_castle_(new Flag_Castle(flag_castle)),
      player_info_(player_info),
      Flag_Pos_X(flag_pole_->Get_Pos().x),
      Castle_Door_X(flag_pole_->Get_Pos().x + 288.0f),
      frame_timer(0.0f),
      current_state(Win_Animation_State::None) {}

Win_Animation_Climb_Flag::~Win_Animation_Climb_Flag()
{
    delete flag_pole_;
    delete flag_castle_;
}

int Win_Animation_Climb_Flag::Calculate_Bonus_Points()
{
    float heightRange = Flag_Bottom_Y - Flag_Top_Y;
    float relativePos = (Flag_Bottom_Y - player_->getPosition().y + player_->get_draw_rec().height) / heightRange; // 1.0 = cao nhất

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

bool Win_Animation_Climb_Flag::Check_Win_Animation()
{
    if (player_->getPosition().x + player_->get_draw_rec().width / 2.0f >= Flag_Pos_X)
    {
        Enter_Win_Animation();
        return true;
    }
    return false;
}

void Win_Animation_Climb_Flag::Enter_Win_Animation()
{
    bonus_points = Calculate_Bonus_Points();
    Score_Manager::GetInstance().AddScore({Flag_Pos_X + 20.0f, player_->getPosition().y - player_->get_draw_rec().height}, bonus_points);
    player_info_.UpdateScore(bonus_points);
    flag_pole_->Set_Velocity({0, Slide_Speed});
    player_->Climb(Slide_Speed);
    player_->Set_Pos({Flag_Pos_X - player_->get_draw_rec().width / 2.0f, player_->getPosition().y});
    Mario_Base_Y = Flag_Bottom_Y + Tile_Size - 10.0f;
    current_state = Win_Animation_State::Climbing;
    player_info_.Game_Won();
    SoundManager::GetInstance().StopMusic();
    SoundManager::GetInstance().PlaySoundEffect("flagpole");
}

void Win_Animation_Climb_Flag::Update(float dt)
{
    flag_pole_->Update(GetFrameTime());
    flag_castle_->Update(GetFrameTime());
    switch (current_state)
    {
    case Win_Animation_State::Climbing:
        Climb_Flag_Pole();
        break;
    case Win_Animation_State::Preparing:
        Prepare_To_Castle();
        break;
    case Win_Animation_State::Going:
        Go_To_Castle();
        break;
    case Win_Animation_State::Posing:
        Pose();
        break;
    case Win_Animation_State::Fading:
        Fade_Out();
        break;
    }
    Raise_Flag();
}

void Win_Animation_Climb_Flag::Draw() const
{
    flag_pole_->Draw();
    flag_castle_->Draw();
}

void Win_Animation_Climb_Flag::Climb_Flag_Pole()
{
    if (player_->getPosition().y >= Mario_Base_Y)
    {
        player_->End_Climb();
    }
    if (flag_pole_->Get_Pos().y >= Flag_Bottom_Y)
    {
        current_state = Win_Animation_State::Preparing;
        flag_pole_->Set_Velocity({0, 0});
        SoundManager::GetInstance().PlaySoundEffect("world_clear");
    }
}

void Win_Animation_Climb_Flag::Prepare_To_Castle()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        current_state = Win_Animation_State::Going;
        frame_timer = 0.0f;
        player_->Set_isGround(true);
        player_->Jump();
        player_->Cut_Jump();
        player_->Cut_Jump();
        return;
    }
    player_->Set_Pos({Flag_Pos_X + player_->get_draw_rec().width / 2.0f, Mario_Base_Y});
    player_->Set_Is_Facing_Right(false);
}

void Win_Animation_Climb_Flag::Go_To_Castle()
{
    player_->MoveRight();
    if (player_->getPosition().x - player_->get_draw_rec().width / 2.0f >= Castle_Door_X)
    {
        current_state = Win_Animation_State::Posing;
        frame_timer = 0.0f;
        player_->Pose(Cool_Down_Time);
    }
}

void Win_Animation_Climb_Flag::Pose()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        current_state = Win_Animation_State::Fading;
        frame_timer = 0.0f;
        player_->Fade_Out(Cool_Down_Time);
    }
}

void Win_Animation_Climb_Flag::Fade_Out()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= Cool_Down_Time)
    {
        frame_timer = 0.0f;
        player_info_.Up_Score();
        current_state = Win_Animation_State::UpScore;
        player_->Set_Disappear(true);
    }
}

bool Win_Animation_Climb_Flag::End_Animation()
{
    if (current_state == Win_Animation_State::Raising && flag_castle_->Get_Velo().y == 0.0f)
        return true;
    return false;
}

void Win_Animation_Climb_Flag::Raise_Flag()
{
    if (player_info_.GetTime() < 0 && current_state == Win_Animation_State::UpScore)
    {
        player_info_.Set_Time_To_0();
        current_state = Win_Animation_State::Raising;
        flag_castle_->Set_Velocity({0, -Slide_Speed / 2.0f});
    }
}
