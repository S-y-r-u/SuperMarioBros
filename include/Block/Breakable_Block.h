#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Breakable_BLock : public A_Block_State
{
private:
    Block &m_block;
    bool is_delete;
    float delta_time;
    Vector2 before_pos;
    Vector2 up_pos_left, down_pos_left;
    const float Move_ = 120.0f;
    const float Break_Height = 45.0f;
    float rotation;
    const float Rotation_Speed = 20.0f;

public:
    Breakable_BLock(Block &block);

    void Draw_() override;
    void Update_() override;
    void On_Hit(std::vector<Item *> &item, Player &player) override {}

    bool Get_Elapse() override;
    bool Get_Is_Delete() const override;
    Rectangle Get_Draw_Rec() const override;

private:
    void Fall_();
    void Be_Delete();
};