#include "Item/Coin.h"

Coin::Coin(Vector2 pos)
    : Item(pos), m_rec(Item_Sprite::Coin::Blinking::blinking_) {}

void Coin::Update_()
{
    appear_animation = 0;
    frame_++;
    if (frame_ >= 10)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0;
    }
    rec_ = m_rec[type_];
}

void Coin::Activate_(Player &player)
{
    player.collectCoin();
    is_delete = 1;
}