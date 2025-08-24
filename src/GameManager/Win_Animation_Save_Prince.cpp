#include "GameManager/Win_Animation_Save_Prince.h"

Win_Animation_Save_Prince::Win_Animation_Save_Prince(Vector2 win_pos, Vector2 pos, PlayerInformation &player_info, Player *&player)
    : kidnap(nullptr),
      prince(nullptr),
      player_info(player_info),
      player(player),
      kidnap_pos(pos),
      win_animation_pos(win_pos),
      timer_(0.0f),
      cur_state(Save_Prince_State::NONE)
{
    // Initialize animations
    kidnap = Animation(&SavePrince::save_prince_, SavePrince::Kidnap::kidnap_, 0.3f);
    prince = Animation(&SavePrince::save_prince_, SavePrince::Prince::prince_, 0.5f);
}

void Win_Animation_Save_Prince::Update(float dt)
{
    switch (cur_state)
    {
    case Save_Prince_State::PLAYER_MOVING:
        Player_Move();
        break;
    case Save_Prince_State::PRINCE_ESCAPING:
        if (kidnap.Get_Frame_Index() == kidnap.Get_Frame_Count() - 1)
            timer_ += dt;
        if (kidnap.Get_Frame_Index() == kidnap.Get_Frame_Count() - 1 && timer_ >= 0.3f - GetFrameTime())
        {
            timer_ = 0.0f;
            cur_state = Save_Prince_State::PRINCE_SAVED;
        }
        if (kidnap.Get_Frame_Index() >= kidnap.Get_Frame_Count() - 2)
            prince.Update(dt);
        kidnap.Update(dt);
        break;
    case Save_Prince_State::PRINCE_SAVED:
        if (prince.Get_Frame_Index() == prince.Get_Frame_Count() - 1)
            timer_ += dt;
        if (timer_ >= 0.5f - GetFrameTime())
        {
            timer_ = 0.0f;
            cur_state = Save_Prince_State::UP_SCORE;
            player_info.Up_Score();
        }
        prince.Update(dt);
        break;
    }
}

void Win_Animation_Save_Prince::Draw() const
{
    if (kidnap.Get_Frame_Index() >= kidnap.Get_Frame_Count() - 2)
    {
        Rectangle prince_rec = prince.Get_Current_Rec();
        Rectangle des_rec = {kidnap_pos.x, kidnap_pos.y, prince_rec.width * scale_screen, prince_rec.height * scale_screen};
        DrawTexturePro(SavePrince::save_prince_.sprite, prince_rec, des_rec, {des_rec.width / 2.0f, des_rec.height}, 0.0f, WHITE);
    }
    if (cur_state == Save_Prince_State::PRINCE_ESCAPING || cur_state == Save_Prince_State::PLAYER_MOVING)
    {
        Rectangle kidnap_rec = kidnap.Get_Current_Rec();
        Rectangle des_rec = {kidnap_pos.x, kidnap_pos.y, kidnap_rec.width * scale_screen, kidnap_rec.height * scale_screen};
        DrawTexturePro(SavePrince::save_prince_.sprite, kidnap_rec, des_rec, {des_rec.width / 2.0f, des_rec.height}, 0.0f, WHITE);
    }
}

bool Win_Animation_Save_Prince::Check_Win_Animation()
{
    if (player->getPosition().x >= win_animation_pos.x)
    {
        Enter_Win_Animation();
        return true;
    }

    return false;
}

void Win_Animation_Save_Prince::Enter_Win_Animation()
{
    cur_state = Save_Prince_State::PLAYER_MOVING;
    player_info.Game_Won();
    SoundManager::GetInstance().StopMusic();
    SoundManager::GetInstance().PlaySoundEffect("world_clear");
}

void Win_Animation_Save_Prince::Player_Move()
{
    player->MoveRight();
    if (player->getPosition().x >= kidnap_pos.x - 60.0f)
    {
        cur_state = Save_Prince_State::PRINCE_ESCAPING;
        player->StopMoving();
    }
}

bool Win_Animation_Save_Prince::End_Animation()
{
    if (player_info.GetTime() <= 0 && cur_state == Save_Prince_State::UP_SCORE)
    {
        player_info.Set_Time_To_0();
        return true;
    }
    return false;
}
