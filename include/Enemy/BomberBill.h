#pragma once
#include "Enemy/Enemy.h"

enum class BomberBill_State
{
    Flying,
    Dying,
    Dead
};

class BomberBill : public Enemy
{
private:
    float max_distance;      // Khoảng cách tối đa có thể chạy
    float initial_x;         // Vị trí x ban đầu
    bool moving_right;       // True nếu đang chạy sang phải, false nếu chạy sang trái
    float run_speed;         // Tốc độ chạy
    Vector2 previous_frame_pos; // Lưu vị trí trước đó để có thể sử dụng trong các thông báo

    // Death animation variables
    BomberBill_State state_;
    float death_timer;
    const float death_duration = 1.0f; // Thời gian rơi trước khi biến mất
    float fall_speed;
    const int score = 100;

public:
    BomberBill(Vector2 startPos, float maxDistance = 300.0f, float speed = 300.0f);
    ~BomberBill();

    void Update(float dt) override;
    void Draw() const override;
    Vector2 Get_Previous_Pos() const override;
    void Set_Pos(Vector2 pos) override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;
    bool Need_Check_Ground_Block() const override;

    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Be_Stomped(PlayerInformation& info) override;

private:
    void Update_Animation(float dt);
    void Start_Death_Animation();
};