#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Normal_Block : public A_Block_State
{
private:
    Block &m_block;
    bool elapse_;
    bool change_state;
    bool is_break;

    Vector2 before_pos;
    float velocity_y;
    const float Push_Height = 150.0f;

public:
    Normal_Block(Block &m_block);

    void Draw_() override;
    void Update_() override;
    void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) override;

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;

    json to_json() const;
    void from_json(const json& j);
private:
    void Elapse_();
    void Change_State();
};
