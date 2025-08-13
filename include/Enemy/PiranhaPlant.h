#pragma once
#include "Enemy.h"

enum class PiranhaPlant_State
{
    underground = 0, // Ẩn trong ống
    emerging,        // Đang nhô lên
    retreating,      // Đang rút xuống
    be_fired_or_hit  // Bị tấn công
};

class PiranhaPlant : public Enemy
{
private:
    PiranhaPlant_State state_;

    // Vị trí cơ bản và thời gian
    Vector2 base_pos;  // Vị trí gốc (trong ống)
    Vector2 above_pos; // Vị trí khi nhô lên hoàn toàn
    float delta_time;
    float state_timer; // Timer cho từng trạng thái

    // Thông số hoạt động
    const float emerge_speed = 60.0f;        // Tốc độ nhô lên/rút xuống
    const float above_duration = 2.0f;       // Thời gian ở trên (giây)
    const float underground_duration = 1.5f; // Thời gian ẩn dưới (giây)
    const float emerge_height = 76.0f;       // Chiều cao nhô lên
    const float Push_Height = 25.0f;         // Độ cao bay lên khi bị đánh

    Player *player;                    // Con trỏ tới player để kiểm tra khoảng cách
    const float safe_distance = 300.0f; // Khoảng cách an toàn từ player
    const int Score_PiranhaPlant = 100;

public:
    PiranhaPlant(Vector2 pos, Player *player_ptr);

    void Draw() const override;
    void Update(float dt) override;
    void Set_Pos(Vector2 pos) override;

    void Notify_Fall(float dt) override;
    void Notify_On_Ground() override;
    void Notify_Be_Stomped(PlayerInformation& info) override;
    void Notify_Be_Fired_Or_Hit(PlayerInformation& info) override;

    bool Can_Be_Stomped() const override;
    bool Can_Be_Fired_Or_Hit() const override;
    bool Need_Check_Ground_Block() const override { return false; } // Không cần kiểm tra block dưới vì chỉ nhô lên/rút xuống

    json to_json() const override;
    void from_json(const json& j) override;

private:
    void UpdateStateMachine(float dt);
    void UpdatePosition(float dt);
    void Animate_();
    void Be_Fired_Or_Hit();
    bool IsPlayerNearby() const;
    float GetCurrentTargetY() const;
};