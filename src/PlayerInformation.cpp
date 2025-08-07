#include "PlayerInformation.h"

PlayerInformation::PlayerInformation(float time, int lives)
{
    score = 0;
    coins = 0;
    this->time = time;
    this->lives = lives;
    coins_frame = 0;
    rec_ = Font_Sprite::Coin::coin[0];
}

PlayerInformation::PlayerInformation(const PlayerInformation &other)
    : score(other.score),
      coins(other.coins),
      world(other.world),
      time(other.time),
      lives(other.lives),
      coin_timer(other.coin_timer),
      coins_frame(other.coins_frame),
      rec_(other.rec_) {}

PlayerInformation& PlayerInformation::operator=(const PlayerInformation &other)
{
    if (this != &other)
    {
        score = other.score;
        coins = other.coins;
        world = other.world;
        time = other.time;
        lives = other.lives;
        coin_timer = other.coin_timer;
        coins_frame = other.coins_frame;
        rec_ = other.rec_;
    }
    return *this;
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
    time -= 2 * dt;
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
    float scale = 3.0f;

    // SCORE
    Font_Sprite::DrawText("SCORE", 50, 50, WHITE);
    std::string score_str = std::to_string(score);
    float score_x = 112 - (score_str.size() * (8 * scale + 1.0f) - 1) / 2.0f;
    Font_Sprite::DrawText(score_str, score_x, 82, WHITE);

    // COINS Icon
    Rectangle dest_rec = {255, 110, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(Font_Sprite::font_.sprite, rec_, dest_rec,
                   {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);

    // COINS Text
    Font_Sprite::DrawText("COINS", 224, 50, WHITE);
    std::string coins_str = "X" + std::to_string(coins);
    float coins_x = 307.0f - (coins_str.size() * (8 * scale + 1.0f) - 1) / 2.0f;
    Font_Sprite::DrawText(coins_str, coins_x, 82, WHITE);

    // WORLD
    Font_Sprite::DrawText("WORLD", 398, 50, WHITE);
    float world_x = 460 - (world.size() * (8 * scale + 1.0f) - 1) / 2.0f;
    Font_Sprite::DrawText(world, world_x, 82, WHITE);

    // TIME
    Font_Sprite::DrawText("TIME", 572, 50, WHITE);
    std::string time_str = std::to_string(static_cast<int>(time));
    float time_x = 621.5f - (time_str.size() * (8 * scale + 1.0f) - 1) / 2.0f;
    Font_Sprite::DrawText(time_str, time_x, 82, WHITE);

    // LIVES
    Font_Sprite::DrawText("LIVES", 721, 50, WHITE);
    std::string lives_str = std::to_string(lives);
    float lives_x = 783 - (lives_str.size() * (8 * scale + 1.0f) - 1) / 2.0f;
    Font_Sprite::DrawText(lives_str, lives_x, 82, WHITE);
}

void PlayerInformation::DecreaseLives()
{
    if (lives > 0)
        --lives;
}

int PlayerInformation::GetLives() const
{
    return lives;
}

void PlayerInformation::ResetTime()
{
    time = 400.0f;
}

void PlayerInformation::ResetCoin()
{
    coins = 0;
    coins_frame = 0;
    rec_ = Font_Sprite::Coin::coin[0];
}

void PlayerInformation::ResetScore()
{
    score = 0;
}

float PlayerInformation::GetTime() const
{
    return time;
}