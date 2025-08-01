#pragma once
#include <string>
#include "sprite.h"

class PlayerInformation {
    private:
        int score;
        int coins;
        std::string world;
        int time;
        int lives;
    public:
        PlayerInformation(); 
        void SetWorld(const std::string &world);
        void Draw() const;      
};