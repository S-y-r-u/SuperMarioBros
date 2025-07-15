#include "Item/HiddenCoin.h"

HiddenCoin::HiddenCoin(Vector2 pos)
    : Item(pos), m_rec(Item_Sprite::Coin::Hidden::hidden_), delta_time(0.0f), before_pos(pos) {}

void HiddenCoin::Update_()
{
    Appear_();
}

void HiddenCoin::Appear_()
{
    const float max_air_time = 2 * push_height / (Physics::gravity_ * 0.12f);
    const int time_transform = (int)(max_air_time * 0.8f) / m_rec.size();

    if (frame_ == 0 && type_ == m_rec.size())
    {
        is_delete = 1;
        return;
    }

    frame_++;
    if (frame_ >= time_transform)
    {
        type_++;
        frame_ = 0;
    }

    if (type_ < m_rec.size())
        rec_ = m_rec[type_];

    delta_time += 0.12f;
    float delta_y = -push_height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
    pos_.y = before_pos.y + delta_y;
}

void HiddenCoin::Activate_(Character &character) {}