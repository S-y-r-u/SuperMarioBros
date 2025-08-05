#include "Item/Coin.h"

Coin::Coin(Vector2 pos)
    : Item(pos),
      m_rec(Item_Sprite::Coin::Blinking::blinking_) {}

void Coin::Update_()
{
    appear_animation = 0;
    frame_ += GetFrameTime();
    if (frame_ >= 1 / 6.0f)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0.0f;
    }
    rec_ = m_rec[type_];
}

void Coin::Activate_(Player &player, PlayerInformation &info)
{
    info.UpdateCoins(1);
    is_delete = 1;
    SoundManager::GetInstance().PlaySoundEffect("coin");
}

bool Coin::Can_Move() const { return false; }