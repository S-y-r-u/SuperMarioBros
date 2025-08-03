#pragma once
#include <string>
#include "sprite.h"

class PlayerInformation {
    private:
        int score;
        int coins;
        std::string world;
        float time;
        int lives;
    public:
        PlayerInformation(); 
        void SetWorld(const std::string &world);
        void UpdateScore(const int &s);
        void UpdateCoins(const int &c);
        void UpdateTime(const float &dt);
        void Draw() const;
};