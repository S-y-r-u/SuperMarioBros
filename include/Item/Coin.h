#pragma once
#include "Item.h"

class Coin : public Item
{
public:
    Coin(Vector2 pos);

    void Update_() override;
    void Appear_() override {}
    void Activate_(Player &player, PlayerInformation &info) override;

    bool Can_Move() const override;

    json to_json() const override;
    void from_json(const json& j) override;
};