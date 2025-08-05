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

    Vector2 previous_frame_pos;
    float stomped_timer;
    const float Stomped_Duration = 0.5f;
    const float Push_Velocity = 200.0f; // Vận tốc khi bị bắn hoặc đánh
    const int Score_Goomba = 100; 

public:
    Goomba(Vector2 pos);

    void Draw() const override;
    void Update(float dt) override;
    void Set_Pos(Vector2 pos) override;
    Vector2 Get_Previous_Pos() const override;

    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Be_Stomped(PlayerInformation& info) override;
    void Notify_Be_Fired_Or_Hit(PlayerInformation& info) override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

private:
    void Move_(float dt);
    void Animate_();
    void Be_Stomped();
    void Be_Fired_Or_Hit(float dt);
};
