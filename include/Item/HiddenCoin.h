#pragma once
#include "Item.h"

class HiddenCoin : public Item
{
private:
    std::vector<Rectangle> m_rec;
    const float Push_Height = 500.0f;

    Vector2 velocity_;
    Vector2 before_pos_;

    float sprite_interval_;

public:
    HiddenCoin(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    void Activate_(Player &player, PlayerInformation &info) override;
    bool Can_Move() const override;
};
