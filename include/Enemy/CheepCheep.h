#pragma once
#include "Enemy/Enemy.h"
#include "Player.h"

class CheepCheep : public Enemy
{
public:
    CheepCheep(Vector2 pos, Player *player, float vx = 150.0f, float vy = -800.0f, float gravity = 500.0f);
    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;
    bool Can_Be_Stomped() const { return true; }
    bool Can_Be_Fired_Or_Hit() const override { return true; }
    bool Need_Check_Map() const override { return false; }
    void Notify_Be_Stomped() override;
    void Notify_Be_Fired_Or_Hit() override;

    json to_json() const override;
    void from_json(const json &j) override;
    enum class CheepCheepState
    {
        Normal,
        Dying
    };

private:
    Player *player;
    Vector2 previous_frame_pos_;
    float base_y_;
    CheepCheepState state_ = CheepCheepState::Normal;
    const float dying_animation_timer = 3.0f;
    const float dying_speed = 600.0f;
    float dying_timer_;
};
