#include "PlayerInformation.h"

PlayerInformation::PlayerInformation()
{
    score = 0;
    coins = 0;
    time = 1000;
    lives = 3;
    coins_frame = 0;
    rec_ = Font_Sprite::Coin::coin[0];
}

void PlayerInformation::SetWorld(const std::string &world)
{
    this->world = world;
}

void PlayerInformation::UpdateScore(const int &s)
{
    score += s;
}

void PlayerInformation::UpdateCoins(const int &c)
{
    coins += c;
}

void PlayerInformation::Update(const float &dt)
{
    time -= dt;
    coin_timer += dt;
    if (coin_timer >= Coin_Animation_Speed)
    {
        coin_timer = 0.0f;
        coins_frame = (coins_frame + 1) % Font_Sprite::Coin::coin.size();
    }
    rec_ = Font_Sprite::Coin::coin[coins_frame];
}

void PlayerInformation::Draw() const
{
    Font_Sprite::DrawText("SCORE", 50, 50); //[50, 174]
    Font_Sprite::DrawText(std::to_string(score), 112 - (std::to_string(score).size() * 25 - 1) / 2.0f, 82);
    Rectangle dest_rec = {255, 110, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(Font_Sprite::font_.sprite, rec_, dest_rec, {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);
    Font_Sprite::DrawText("COINS", 224, 50); //[224, 348]
    std::string text = "X" + std::to_string(coins);
    float text_width = text.size() * 25.0f;
    Font_Sprite::DrawText(text, 270.0f, 82.0f);
    Font_Sprite::DrawText("WORLD", 398, 50); //[398, 522]
    Font_Sprite::DrawText(world, 460 - (world.size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("TIME", 572, 50); //[572, 671]
    Font_Sprite::DrawText(std::to_string(int(time)), 621.5f - (std::to_string(int(time)).size() * 25 - 1) / 2.0f, 82);
    Font_Sprite::DrawText("LIVES", 721, 50); //[721, 845]
    Font_Sprite::DrawText(std::to_string(lives), 783 - (std::to_string(lives).size() * 25 - 1) / 2.0f, 82);
}