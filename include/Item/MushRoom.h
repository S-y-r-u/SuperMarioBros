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
    Vector2 velocity_;
    Vector2 previous_frame_pos;
    const float Mushroom_Ini_Velo = 300.0f;
    Vector2 before_pos_;
    const int Score_One_Up_Super = 1000;

public:
    Mush_Room(Vector2 pos, State_MushRoom state);

    void Update_() override;
    //
    void Activate_(Player &player, PlayerInformation &info) override;

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
    bool Can_Move() const override;

    json to_json() const override;
    void from_json(const json& j) override;
};