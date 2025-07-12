#pragma once
#include "Item.h"

class Coin : public Item
{
private:
    std::vector<Rectangle> m_rec;

public:
    Coin(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    void Activate_(Character &character) override;
};