#pragma once
#include "Enemy.h"
#include "Player/Player.h"
#include "Spiny.h"
#include <raymath.h>
#include <unordered_map>

enum class Latiku_State
{
    fly,
    throw_spiny,
    be_fired_or_hit,
    disappear
};

class Latiku : public Enemy
{
private:
    Latiku_State state_;

    float timer_;
    const float throw_interval = 1.6f;
    const float throw_duration = 0.25f;
    const float hover_radius = 200.0f;
    const float hover_speed = 3.0f;
    float pos_to_player;
    bool pos_state;
    float base_y;
    const float Push_Velocity = 200.0f;
    const float dis_to_finish = 2 * Screen_w;

    Player *&player;
    std::vector<Enemy *> *enemies;
    std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map;
    Camera2D &camera;

public:
    Latiku(Vector2 pos, Player *&player, std::vector<Enemy *> *enemies, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map, Camera2D &camera);

    void Update(float dt) override;
    void Draw() const override;

    void Notify_Be_Fired_Or_Hit() override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

    bool Need_Check_Map() const override;

    json to_json() const override;
    void from_json(const json &j) override;

private:
    void Spawn_Spiny();
    void Animate_(float dt);
    void Disappear_(float dt);
};
