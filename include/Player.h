#pragma once
#include "Character.h"
#include "Menu/SoundManager.h"
#include <vector>

enum class PlayerForm {Small, Super, Invincible, Invincible_Super_And_Fire, Fire};

enum class AnimationState {Stance, Jump, Die, Walk, Slide, Climb, Crouch, Enter_Pipe, Fade_Out, Small_To_Super,
Stance_To_Fire, Crouch_To_Fire, Jump_To_Fire, Walk_To_Fire, Slide_To_Fire, Climb_To_Fire, Shoot, Hit, Shoot_Fire};

class Player : public Character{
    protected:
        PlayerForm form;
        AnimationState state;
        float JumpForce;
        float friction;

        bool isTransforming;
        PlayerForm targetForm;
        Rectangle previous_frame_rec ;

        bool isInvincible;
        float invincibleTimer;
        PlayerForm beforeStar;

        bool isDead;
        float deadTimer;

        int currentFrame;
        float frameTimer;
        float animationSpeed;

        virtual std::vector<Rectangle>& getAnimationFrame() const = 0;

    public:
        Player(Vector2 startPos);
        virtual ~Player();

        Rectangle get_draw_rec() override;
        Rectangle Get_Previous_Rec() override;
        AnimationState get_state() const;
        PlayerForm get_form() const; 
        Vector2 get_Velocity() const { return velocity; }
        void Set_Velocity(Vector2 newVelocity) { velocity = newVelocity; }
        bool Get_isGround() const { return isGround; }
        void Set_isGround(bool value) { isGround = value; }
        bool Get_isTransforming() const { return isTransforming; }
        bool Get_isInvincible() const { return isInvincible; }
        PlayerForm Get_formBeforeStar() const {return beforeStar; }
        bool Get_isDead() const { return isDead; }
    
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

        void Die();
};