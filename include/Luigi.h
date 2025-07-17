#pragma once
#include "Player.h"

class Luigi : public Player{
    public:
        Luigi(Vector2 startPos);
    protected:
        std::vector<Rectangle>& getAnimationFrame() const;
};