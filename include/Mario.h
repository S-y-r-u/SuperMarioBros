#pragma once
#include "Player.h"

class Mario : public Player{
    public:
        Mario(Vector2 startPos);
    protected:
        std::vector<Rectangle>& getAnimationFrame() const;
};