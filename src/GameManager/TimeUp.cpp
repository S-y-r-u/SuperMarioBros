#include "GameManager/TimeUp.h"

TimeUp::TimeUp() : player_info(nullptr), timer_(0.0f) {}

void TimeUp::SetPlayerInformation(PlayerInformation *info)
{
    player_info = info;
}

void TimeUp::Draw() const
{
    ClearBackground(BLACK);
    if (player_info)
    {
        player_info->Draw();
    }
    Rectangle destRect = {(Screen_w - Screen_Sprite::time_up_word.width * 5.0f) / 2.0f, (Screen_h - Screen_Sprite::time_up_word.height * 5.0f) / 2.0f, (float)Screen_Sprite::time_up_word.width * 5.0f, (float)Screen_Sprite::time_up_word.height * 5.0f};
    DrawTexturePro(Screen_Sprite::screen_.sprite, Screen_Sprite::time_up_word, destRect, {0, 0}, 0.0f, WHITE);
}

int TimeUp::Update()
{
    timer_ += GetFrameTime();
    if (timer_ >= time_to_show)
    {
        timer_ = 0.0f;
        return menuState;
    }
    return timeUpState;
}