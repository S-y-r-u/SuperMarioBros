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
        PlayerInformation(); 
        void SetWorld(const std::string &world);
        void UpdateScore(const int &s);
        void UpdateCoins(const int &c);
        void Update(const float &dt);
        void Draw() const;
};