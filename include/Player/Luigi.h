#pragma once
#include "Player.h"

class Luigi : public Player{
    public:
        Luigi(Vector2 startPos);
        virtual ~Luigi();
    protected:
        std::vector<Rectangle>& getAnimationFrame() const;
};