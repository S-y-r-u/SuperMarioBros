#pragma once
#include "Character.h"
#include <vector>

enum class PlayerForm {Small, Super, Invincible};

enum class AnimationState {Stance, Jump, Die, Walk, Slide, Climb, Crouch};

class Player : public Character{
    protected:
        PlayerForm form;
        AnimationState state;
        int currentFrame;
        float frameTimer;
        float animationSpeed;

        virtual std::vector<Rectangle>& getAnimationFrame() const = 0;
    public:
        Player(Vector2 startPos);
        virtual ~Player();
        void MoveRight() override;
        void MoveLeft() override;
        void update(float dt) override;
        void draw() override;
        
};