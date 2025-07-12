#pragma once
#include "Item.h"

constexpr float star_ini_velo = 30.0f;

class Star : public Item
{
private:
    bool direct_, is_appear;
    float delta_time;
    Vector2 before_pos;

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
    void Activate_(Character &character) override;
};