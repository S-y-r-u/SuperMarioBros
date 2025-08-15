#pragma once
#include "Constants.h"
#include "Sprite.h"
#include "GameManager/DrawScore.h"
#include "GameManager/PlayerInformation.h"
#include "GameManager/Animation.h"
#include <raymath.h>

class Enemy
{
protected:
    Animation animation_;
    Vector2 position_;
    Vector2 velocity_;
    float gravity_;
    bool is_ground;
    bool is_active, is_dead;
    bool first_appear = false;
    int score;
public:
    Enemy(Vector2 start_pos, Vector2 velocity, float gravity);
    virtual ~Enemy();

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;
    virtual Vector2 Get_Previous_Pos() const {}

    bool Get_First_Appear() const { return first_appear; }
    void Set_First_Appear(bool value) { first_appear = value; }

    Rectangle Get_Draw_Rec() const;
    Vector2 Get_Pos() const;
    Vector2 Get_Velocity() const;
    void Set_Velocity(Vector2 velocity);
    virtual void Set_Pos(Vector2 pos) {}
    bool Get_Is_Active();
    bool Get_Is_Dead();
    int Get_Score();

    virtual bool Can_Be_Stomped() const = 0;
    virtual bool Can_Be_Fired_Or_Hit() const = 0;
    virtual bool Can_Be_Kicked() const;
    virtual bool Can_Jump() const;

    virtual bool Need_Check_Map() const;

    virtual void Notify_Fall(float dt) {}
    virtual void Notify_On_Ground() {}
    virtual void Notify_Jump() {}

    void Notify_Change_Direct();

    virtual json to_json() const = 0;
    virtual void from_json(const json& j) = 0;

    virtual void Notify_Be_Stomped() {}
    virtual void Notify_Be_Fired_Or_Hit() {}
    virtual void Notify_Be_Kicked(int direction) {}

    virtual void Collision_With_Other_Enemy(Enemy *other);
    virtual bool Kill_Enemy();
};
