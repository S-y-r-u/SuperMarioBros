#pragma once
#include "Item.h"

class Star : public Item
{
private:
    bool direct_, is_appear;
    Vector2 before_pos;
    Vector2 previous_frame_pos;

    Vector2 velocity_; // thêm velocity_

    const float Star_Ini_Velo = 300.0f;
    const int Score_Star = 1000;

public:
    Star(Vector2 pos);

    void Notify_On_Ground() override;
    void Notify_Change_Direct() override;

    void Fall_(float dt);
    void Move_(float dt);
    void Be_Delete();

    void Appear_() override;
    void Update_() override;
    void Activate_(Player &player, PlayerInformation &info) override;

    Vector2 Get_Previous_Frame_Pos() override;
    bool Get_Direct() const;
    bool Can_Move() const override;

    json to_json() const override;
    void from_json(const json& j) override;
};
