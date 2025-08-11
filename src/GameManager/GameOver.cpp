#include "GameManager/GameOver.h"

GameOver::GameOver() : timer_(0.0f), player_info(nullptr) {}

void GameOver::SetPlayerInformation(PlayerInformation *info)
{
    player_info = info;
}

void GameOver::Draw() const
{
    ClearBackground(BLACK); 
    if (player_info)
    {
        player_info->Draw();
    }
    Rectangle destRect = {(Screen_w - Screen_Sprite::game_over_word.width * 5.0f) / 2.0f, 
        (Screen_h - Screen_Sprite::game_over_word.height * 5.0f) / 2.0f, 
        (float)Screen_Sprite::game_over_word.width * 5.0f, (float)Screen_Sprite::game_over_word.height * 5.0f};
    DrawTexturePro(Screen_Sprite::screen_.sprite, Screen_Sprite::game_over_word, destRect, {0, 0}, 0.0f, WHITE);
}

int GameOver::Update()
{
    timer_ += GetFrameTime();
    if (timer_ >= time_to_show)
    {
        timer_ = 0.0f;
        return menuState;
    }
    return gameOverState;
}