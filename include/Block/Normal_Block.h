#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Normal_Block : public A_Block_State
{
private:
    Block &m_block;
    Vector2 before_pos;
    float delta_time;
    bool elapse_;
    bool change_state;
    bool has_item, is_break;

public:
    Normal_Block(Block &m_block);

    void Draw_() override;
    void Update_() override;
    // Kiểm tra điều kiện của character
    void On_Hit(std::vector<Item *> &item, Player &player) override;

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;

private:
    void Elapse_();
    void Change_State();
};