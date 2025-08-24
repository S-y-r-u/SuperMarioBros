#pragma once
#include "Enemy.h"

class LaserFire : public Enemy
{
public:
    // pos: vị trí bắt đầu, target: vị trí mục tiêu, speed: vận tốc tia lửa
    LaserFire(Vector2 pos, Vector2 target, float speed = 350.0f);
    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;
    bool Can_Be_Stomped() const override { return false; }
    bool Can_Be_Fired_Or_Hit() const override { return false; }

    bool Need_Check_Map() const override { return false; }

    void Notify_Be_Fired_Or_Hit() override { is_active = false; is_dead = true; }
    void Notify_Fall(float dt) override {}
    void Notify_On_Ground() override {}

    json to_json() const override;
    void from_json(const json &j) override;

private:
    Vector2 previous_frame_pos_;
    float life_time_ = 4.0f; // tồn tại 4s
};
