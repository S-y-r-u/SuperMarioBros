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
    bool direct_, fall_, is_appear, jump_;
    float delta_time;
    Vector2 before_pos;
    Vector2 previous_frame_pos;
    const float Mushroom_Ini_Velo = 30.0f;

public:
    Mush_Room(Vector2 pos, State_MushRoom state);

    void Update_() override;
    //
    void Activate_(Player &player) override;

    void Fall_();
    void Move_();
    void Jump_();
    void Be_Delete();
    void Appear_() override;

    void Notify_Fall() override;
    void Notify_On_Ground() override;
    void Notify_Change_Direct() override;
    void Notify_Jump();

    Vector2 Get_Previous_Frame_Pos() override;
    bool Get_Direct() const;
};