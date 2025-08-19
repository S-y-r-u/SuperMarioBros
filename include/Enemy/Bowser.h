#pragma once
#include "Enemy/Enemy.h"
#include "Player.h"
#include "Enemy/LaserFire.h"

enum class Bowser_State
{
    normal = 0,
    fire,
    dying
};


class Bowser : public Enemy
{
private:
    Bowser_State state_;
    Vector2 previous_frame_pos;
    const float Push_Velocity = 200.0f; // Vận tốc khi bị bắn hoặc đánh
    std::vector<Enemy*>& enemies_;
    // Thuộc tính mới
    int hp_;
    float fire_cooldown_;
    float fire_timer;
    bool is_firing_;
    bool is_jumping_;
    const float jump_velocity_ = 0.0f;
    const float detect_range_ = 1000.0f;
    const float jump_power_ = 300.0f;
    const float x_min_ = 6300.0f; // Giới hạn trái
    const float x_max_ = 6850.0f; // Giới hạn phải
    const float dying_up = 0.2f; 
    const float dying_down = 2.0f;
    Player* target_player_;
    float jump_cooldown_;
    const float jump_cooldown_duration_ = 3.0f;
    bool face_right_ = true; // true: quay phải, false: quay trái


public:
    Bowser(Vector2 pos, Player* player , std::vector<Enemy*>& enemies);

    // Giữ nguyên các hàm cũ
    void Draw() const override;
    void Update(float dt) override;
    void Set_Pos(Vector2 pos) override;
    Vector2 Get_Previous_Pos() const override;
    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Be_Fired_Or_Hit() override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;

    json to_json() const;
    void from_json(const json& j);

private:
    void Move_(float dt);
    void Animate_();
    void Be_Dying(float dt);
    float dying_time_ = 0.0f;
    void AI_jump();
};
