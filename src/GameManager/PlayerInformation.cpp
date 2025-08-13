#include "GameManager/PlayerInformation.h"

PlayerInformation::PlayerInformation(float time, int lives)
    : animation_(&Font_Sprite::font_, Font_Sprite::Coin::coin, 1 / 6.0f),
      score(0),
      coins(0),
      time(time),
      lives(lives),
      is_game_won(false),
      up_score(false) {}

PlayerInformation::PlayerInformation(const PlayerInformation &other)
    : score(other.score),
      coins(other.coins),
      world(other.world),
      time(other.time),
      lives(other.lives),
      is_game_won(other.is_game_won),
      up_score(other.up_score),
      animation_(other.animation_) {}

PlayerInformation &PlayerInformation::operator=(const PlayerInformation &other)
{
    if (this != &other)
    {
        score = other.score;
        coins = other.coins;
        world = other.world;
        time = other.time;
        lives = other.lives;
        is_game_won = other.is_game_won;
        up_score = other.up_score;
        animation_ = other.animation_;
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
    if (!is_game_won && !up_score)
        time -= 2 * dt;
    else if (up_score)
    {
        time -= 40 * dt;
        score += 20;
    }
    animation_.Update(dt);
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
    Rectangle dest_rec = {255, 110, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(Font_Sprite::font_.sprite, animation_.Get_Current_Rec(), dest_rec,
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
}

void PlayerInformation::ResetScore()
{
    score = 0;
}

float PlayerInformation::GetTime() const
{
    return time;
}

void PlayerInformation::Game_Won()
{
    is_game_won = true;
}

void PlayerInformation::Up_Score()
{
    up_score = true;
}

void PlayerInformation::Set_Time_To_0()
{
    time = 0;
    up_score = false;
    is_game_won = true;
}


json PlayerInformation::to_json() const {
    nlohmann::json j;
    j["score"] = score;
    j["coins"] = coins;
    j["world"] = world;
    j["time"] = time;
    j["lives"] = lives;
    j["is_game_won"] = is_game_won;
    j["up_score"] = up_score;
    return j;
}

void PlayerInformation::from_json(const nlohmann::json &j) {
    score = j.at("score").get<int>();
    coins = j.at("coins").get<int>();
    world = j.at("world").get<std::string>();
    time = j.at("time").get<float>();
    lives = j.at("lives").get<int>();
    is_game_won = j.at("is_game_won").get<bool>();
    up_score = j.at("up_score").get<bool>();
}