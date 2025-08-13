#pragma once
#include "Character.h"
#include "FireBall.h"
#include "Menu/SoundManager.h"
#include <vector>

enum class PlayerForm {Small, Super, Invincible, Invincible_Super_And_Fire, Fire};

enum class AnimationState {Stance, Jump, Die, Walk, Slide, Climb, Crouch, Enter_Pipe, Fade_Out, Small_To_Super,
Stance_To_Fire, Crouch_To_Fire, Jump_To_Fire, Walk_To_Fire, Slide_To_Fire, Climb_To_Fire, Shoot, Hit, Shoot_Fire, Pose};

class Player : public Character{
    protected:
        PlayerForm form;
        AnimationState state;
        float JumpForce;
        float friction;

        bool isTransforming;
        PlayerForm targetForm;

        bool isInvincible;
        float invincibleTimer;
        PlayerForm beforeStar;

        bool isDead;
        bool isActive;
        float deadTimer;
        Vector2 climb_velo;
        bool is_climbing;

        float fireCoolDown;
        
        int currentFrame;
        float frameTimer;
        float animationSpeed;
        float animationSpeedClimb;

        bool is_pose;
        bool is_fade_out;

        virtual std::vector<Rectangle>& getAnimationFrame() const = 0;

    public:
        Player(Vector2 startPos);
        virtual ~Player();

        Rectangle get_draw_rec() override;
        AnimationState get_state() const { return state; }; 
        PlayerForm get_form() const { return form; }; 
        Vector2 get_Velocity() const { return velocity; }
        void Set_Velocity(Vector2 newVelocity) { velocity = newVelocity; }
        bool Get_isGround() const { return isGround; }
        void Set_isGround(bool value);
        void Set_Is_Facing_Right(bool value);
        bool Get_isTransforming() const { return isTransforming; }
        bool Get_isInvincible() const { return isInvincible; }
        PlayerForm Get_formBeforeStar() const {return beforeStar; }
        bool Get_isDead() const { return isDead; }
        bool Get_isActive() const { return isActive; }
    
        void MoveRight() override;
        void MoveLeft() override;
        void StopMoving() override;
        void Jump();
        void Cut_Jump();

        void update(float dt) override;
        void draw() override;

        void collectCoin();
        void getMushroom();
        void getFlower();
        void getStar();

        void Climb(float slide_speed);
        void End_Climb();

        void Die();
        
        void updateCoolDown(float dt);
        void Shoot(std::vector<FireBall*> &fireballs);

        void Pose(float dt);
        void Fade_Out(float dt);

        json to_json() const;
        void from_json(const json& j);
};