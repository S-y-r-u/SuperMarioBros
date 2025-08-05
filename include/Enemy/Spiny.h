#pragma once
#include "Enemy.h"

enum class Spiny_State
{
    egg = 0,
    normal,
    be_fired_or_hit
};

class Spiny : public Enemy
{
private:
    Spiny_State state_;
    std::vector<Rectangle> m_egg;
    std::vector<Rectangle> m_normal;

    Vector2 previous_frame_pos;
    bool is_jump;
    bool prev_ground;
    const float Push_Velocity = 200.0f; 
    const float Jump_Velocity = 400.0f;
    const int Score_Spiny = 100; 

public:
    Spiny(Vector2 pos, Vector2 velo);

    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;

    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Jump() override;
    void Notify_Be_Stomped(PlayerInformation& info) override {}
    void Notify_Be_Fired_Or_Hit(PlayerInformation& info) override;

    void Set_Pos(Vector2 pos) override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;
    bool Can_Jump() const override;
    void Collision_With_Other_Enemy(Vector2 velo, Vector2 pos) override;

private:
    void Animate_();
    void Move_(float dt);
    void Be_Fired_Or_Hit(float dt);
};
