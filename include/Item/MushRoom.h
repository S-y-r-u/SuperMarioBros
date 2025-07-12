#pragma once
#include "Item.h"

enum State_MushRoom
{
    super_ = 0,
    one_up,
    posion_
};

class Mush_Room : public Item
{
private:
    State_MushRoom state_;
    bool direct_, fall_, is_appear;
    float delta_time;
    Vector2 before_pos;

public:
    Mush_Room(Vector2 pos, State_MushRoom state);

    void Update_() override;
    //
    void Activate_(Character &character) override;

    void Fall_();
    void Move_();
    void Be_Delete();
    void Appear_() override;

    void Notify_Fall() override;
    void Notify_On_Ground() override;
    void Notify_Change_Direct() override;
};