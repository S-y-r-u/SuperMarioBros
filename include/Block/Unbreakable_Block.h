#pragma once
#include "Block.h"
#include "RotatingBar.h"
#include "Abstract_Block_State.h"

class Unbreakable_Block : public A_Block_State
{
private:
    Block &m_block;
    RotatingBar* m_rotating_bar;
    bool first_appear;

public:
    Unbreakable_Block(Block &m_block);
    ~Unbreakable_Block();

    void Draw_() override;
    void Update_() override;
    void On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info) override ;
    bool Kill_Player(Player &player, Camera2D& camera) override;

    bool Get_Elapse() override;
    Rectangle Get_Draw_Rec() const override;

        // Serialize/Deserialize
    json to_json() const;
    void from_json(const json& j);
};