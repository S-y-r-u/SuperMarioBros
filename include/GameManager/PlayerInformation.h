#pragma once
#include <string>
#include "sprite.h"
#include "Constants.h"

class PlayerInformation {
    private:
        int score;
        int coins;
        std::string world;
        float time;
        int lives;
        
        float coin_timer = 0.0f;
        const float Coin_Animation_Speed = 1.0f / 5.0f; 
        int coins_frame;
        Rectangle rec_;
    public:
        PlayerInformation(float time, int lives); 
        PlayerInformation(const PlayerInformation &other);
        PlayerInformation& operator=(const PlayerInformation &other);
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
};