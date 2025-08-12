#pragma once
#include <string>
#include "sprite.h"
#include "Constants.h"
#include "Animation.h"

class PlayerInformation
{
private:
    int score;
    int coins;
    std::string world;
    float time;
    int lives;
    bool is_game_won;
    bool up_score;

    Animation animation_;

public:
    PlayerInformation(float time, int lives);
    PlayerInformation(const PlayerInformation &other);
    PlayerInformation &operator=(const PlayerInformation &other);
    void SetWorld(const std::string &world);
    void UpdateScore(const int &s);
    void UpdateCoins(const int &c);
    void DecreaseLives();
    int GetLives() const;
    float GetTime() const;
    void ResetTime();
    void ResetCoin();
    void ResetScore();
    void Update(const float &dt);
    void Draw() const;
    void Game_Won();
    void Up_Score();
    void Set_Time_To_0();
};