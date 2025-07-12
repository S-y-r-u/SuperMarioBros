#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Question_Block : public A_Block_State
{
private:
    Block &m_block;
    std::vector<Rectangle> m_rec;
    int frame_, type_;
    Vector2 before_pos;
    float delta_time;
    bool elapse_;

public:
    Question_Block(Block &m_block);

    void Draw_() override;
    void Update_() override;
    void On_Hit(std::vector<Item *> &item, Character &character) override;

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;

private:
    void Animation_();
    void Elapse_();
    void Change_State();
};