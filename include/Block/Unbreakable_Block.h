#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Unbreakable_Block : public A_Block_State
{
private:
    Block &m_block;

public:
    Unbreakable_Block(Block &Block);

    void Draw_() override;
    void Update_() override {}
    void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) override {}

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;
};