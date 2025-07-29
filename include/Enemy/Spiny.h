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

    // Dung trong fall
    Vector2 before_pos;
    Vector2 previous_frame_pos;
    float delta_time;
    bool is_jump;
    const float Push_Height = 25.0f;
    const float Ini_Velo = 40.0f;

public:
    Spiny(Vector2 pos, Vector2 velo, float gravity);

    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;
    
    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Jump();
    void Notify_Be_Stomped() override {}
    void Notify_Be_Fired_Or_Hit() override;

    void Set_Pos(Vector2 pos) override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

private:
    void Animate_();
    void Fall_();
    void Move_(float dt);
    void Jump_(float dt);
    void Be_Fired_Or_Hit();
};
