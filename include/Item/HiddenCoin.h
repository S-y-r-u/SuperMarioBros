#pragma once
#include "Item.h"

class HiddenCoin : public Item
{
private:
    float delta_time;
    Vector2 before_pos;
    std::vector<Rectangle> m_rec;
    const float Push_Height = 48.0f;

public:
    HiddenCoin(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    //
    void Activate_(Player &player) override;
};