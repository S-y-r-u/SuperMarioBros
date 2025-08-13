#pragma once
#include "Block.h"
#include "Abstract_Block_State.h"

class Question_Block : public A_Block_State
{
private:
    Block &m_block;
    Vector2 before_pos;
    float velocity_y;
    const float Push_Height = 150.0f;
    bool elapse_;

public:
    Question_Block(Block &m_block);

    void Draw_() override;
    void Update_() override;
    void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) override;

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;

        // Serialize/Deserialize
    json to_json() const;
    void from_json(const json& j);
private:
    void Animation_();
    void Elapse_();
    void Change_State();
};
