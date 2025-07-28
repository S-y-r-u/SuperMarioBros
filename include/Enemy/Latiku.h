#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Spiny.h"
#include <raymath.h>

enum class Latiku_State
{
    fly,
    throw_spiny,
    be_fired_or_hit
};

class Latiku : public Enemy
{
private:
    Latiku_State state_;

    Vector2 before_pos;
    float delta_time;

    float timer_;
    const float throw_interval = 2.0f;
    const float throw_duration = 0.25f;
    const float hover_radius_front = 250.0f;
    const float hover_radius_back = 150.0f;
    const float hover_speed = 3.0f;
    float pos_to_player;
    bool pos_state;
    float base_y;
    const float Push_Height = 25.0f;

    Player *player;
    std::vector<Enemy *> *enemies;

public:
    Latiku(Vector2 pos, float gravity, Player *player, std::vector<Enemy *> *enemies);

    void Update(float dt) override;
    void Draw() const override;

    void Notify_Fall(float dt) override {}
    void Notify_On_Ground() override {}
    void Notify_Be_Stomped() override {}
    void Notify_Be_Fired_Or_Hit() override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

private:
    void Be_Fired_Or_Hit();
    void Spawn_Spiny();
    void Animate_(float dt);
};
