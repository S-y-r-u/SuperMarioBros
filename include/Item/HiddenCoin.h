#pragma once
#include "Item.h"

constexpr float push_height = 48.0f;

class HiddenCoin : public Item
{
private:
    float delta_time;
    Vector2 before_pos;
    std::vector<Rectangle> m_rec;

public:
    HiddenCoin(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    //
    void Activate_(Character &character) override;
};