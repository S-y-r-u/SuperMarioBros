#pragma once
#include "Enemy.h"

enum class Goomba_State
{
    normal = 0,
    be_stomped,
    be_fired_or_hit
};

class Goomba : public Enemy
{
private:
    Goomba_State state_;
    std::vector<Rectangle> m_normal;

    // Dùng trong fall
    Vector2 before_pos;
    Vector2 previous_frame_pos;
    float delta_time;
    const float Push_Height = 25.0f;

    int stomped_timer = 0;
    const int Stomped_Duration = 30;

public:
    Goomba(Vector2 pos, Vector2 velo, float gravity);

    void Draw() const override;
    void Update(float dt) override;
    void Set_Pos(Vector2 pos) override;
    Vector2 Get_Previous_Pos() const override;

    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Be_Stomped() override;
    void Notify_Be_Fired_Or_Hit() override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

private:
    void Fall_();
    void Move_(float dt);
    void Animate_();
    void Be_Stomped();
    void Be_Fired_Or_Hit();
};
