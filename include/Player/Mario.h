#pragma once
#include "Player.h"

class Mario : public Player{
    public:
        Mario(Vector2 startPos);
        virtual ~Mario();
    protected:
        std::vector<Rectangle>& getAnimationFrame() const;
};