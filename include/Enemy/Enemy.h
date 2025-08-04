#pragma once
#include "Constants.h"
#include "Sprite.h"
#include "DrawScore.h"
#include "PlayerInformation.h"
#include <raymath.h>

class Enemy
{
protected:
    const SpriteSheet& sprite_;
    Vector2 position_;
    Vector2 velocity_;
    Rectangle rec_;
    float gravity_;
    float frame_timer;
    const float animation_speed = 1.0f / 5.0f;
    int current_frame;
    bool is_ground;
    bool is_active, is_dead;

public:
    Enemy(Vector2 startPos, Vector2 velocity, float gravity);
    virtual ~Enemy();

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;
    virtual Vector2 Get_Previous_Pos() const {}

    Rectangle Get_Draw_Rec() const;
    Vector2 Get_Pos() const;
    Vector2 Get_Velocity() const;
    virtual void Set_Pos(Vector2 pos) {}
    bool Get_Is_Active();
    bool Get_Is_Dead();

    virtual bool Can_Be_Stomped() const = 0;
    virtual bool Can_Be_Fired_Or_Hit() const = 0;
    virtual bool Can_Be_Kicked() const;
    virtual bool Can_Jump() const;
    virtual bool Need_Check_Ground_Block() const;
    virtual bool Kill_Other_Enemies() const;

    virtual void Notify_Fall(float dt) {}
    virtual void Notify_On_Ground() {}
    virtual void Notify_Jump() {}
    void Notify_Change_Direct();
    virtual void Notify_Be_Stomped(PlayerInformation& info) {}
    virtual void Notify_Be_Fired_Or_Hit(PlayerInformation& info) {}
    virtual void Notify_Be_Kicked(int direction, PlayerInformation& info) {}
};
