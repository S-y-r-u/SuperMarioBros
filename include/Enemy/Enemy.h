#pragma once
#include "Constants.h"
#include "Sprite.h"
#include <raymath.h>

class Enemy
{
protected:
    SpriteSheet sprite_;
    Vector2 position_;
    Vector2 velocity_;
    Rectangle rec_;
    float gravity_;
    int frame_timer, current_frame;
    bool is_ground;
    bool be_fired, be_stomped;
    bool is_active, is_dead;

public:
    Enemy(Vector2 startPos, Vector2 velocity, float gravity);
    virtual ~Enemy();

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;

    Rectangle Get_Draw_Rec() const;
    Vector2 Get_Pos() const;
    virtual void Set_Pos(Vector2 pos) {}
    bool Get_Is_Active();
    bool Get_Is_Dead();

    virtual bool Can_Be_Stomped() const = 0;
    virtual bool Can_Be_Fired_Or_Hit() const = 0;

    virtual void Notify_Fall(float dt);
    virtual void Notify_On_Ground();
    void Notify_Change_Direct();
    virtual void Notify_Be_Stomped() {}
    virtual void Notify_Be_Fired_Or_Hit() {}
};
