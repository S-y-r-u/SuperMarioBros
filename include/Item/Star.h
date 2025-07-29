#pragma once
#include "Item.h"

class Star : public Item
{
private:
    bool direct_, is_appear;
    float delta_time;
    Vector2 before_pos;
    Vector2 previous_frame_pos;
    const float Star_Ini_Velo = 30.0f;

public:
    Star(Vector2 pos);

    void Notify_On_Ground() override;
    void Notify_Change_Direct() override;

    void Fall_();
    void Move_();
    void Be_Delete();

    void Appear_() override;
    void Update_() override;
    //
    void Activate_(Player &player) override;

    Vector2 Get_Previous_Frame_Pos() override;
    bool Get_Direct() const;
};