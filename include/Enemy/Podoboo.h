#pragma once
#include "Enemy.h"

class Podoboo : public Enemy
{
public:
    Podoboo(Vector2 pos, float speed = 600.0f);
    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;

    bool Can_Be_Stomped() const override { return false; }
    bool Can_Be_Fired_Or_Hit() const override { return false; }

    bool Need_Check_Map() const override { return false; }

    json to_json() const override;
    void from_json(const json &j) override;

private:
    Vector2 previous_frame_pos_;
    float base_y_;
    const float jump_height_ = 800.0f;
    bool going_up_ = true;
};
