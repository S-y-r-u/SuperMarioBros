#pragma once
#include "Player.h"

class Luigi : public Player{
    public:
        Luigi(Vector2 startPos);
        Luigi(const Player& other);
        virtual ~Luigi();
    protected:
        std::vector<Rectangle>& getAnimationFrame() const;
};