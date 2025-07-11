#pragma once
#include "Item.h"

class Flower : public Item
{
private:
    bool is_appear;
    Vector2 before_pos;

public:
    Flower(Vector2 pos);

    void Update_() override;
    void Appear_() override;
    //
    void Activate_(Character &character) override;
};