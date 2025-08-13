#pragma once
#include "Item.h"

class Flower : public Item
{
private:
    bool is_appear;
    Vector2 before_pos;
    const int Score_Flower = 1000;

public:
    Flower(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    //
    void Activate_(Player &player, PlayerInformation &info) override;

    bool Can_Move() const override;

    json to_json() const override;
    void from_json(const json& j) override;
};