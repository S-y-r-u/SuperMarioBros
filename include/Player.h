#pragma once
#include "Character.h"
#include <vector>

enum class PlayerForm {Small, Super, Invincible, Invincible_Super_And_Fire, Fire};

enum class AnimationState {Stance, Jump, Die, Walk, Slide, Climb, Crouch, Enter_Pipe, Fade_Out, Small_To_Super,
Stance_To_Fire, Crouch_To_Fire, Jump_To_Fire, Walk_To_Fire, Slide_To_Fire, Climb_To_Fire, Shoot, Hit, Shoot_Fire};

class Player : public Character{
    protected:
        PlayerForm form;
        AnimationState state;
        bool isGround = 1;
        int currentFrame;
        float frameTimer;
        float animationSpeed;
        virtual std::vector<Rectangle>& getAnimationFrame() const = 0;

    public:
        Player(Vector2 startPos);
        virtual ~Player();

        Rectangle get_draw_rec() override;
        AnimationState get_state() const;
        PlayerForm get_form() const;

        void MoveRight() override;
        void MoveLeft() override;
        void StopMoving() override;
        void Jump();

        void update(float dt) override;
        void draw() override;

        void collectCoin();
        void getMushroom();
        void getFlower();
        void getStar();
};