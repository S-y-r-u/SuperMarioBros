#include "Item/Coin.h"

Coin::Coin(Vector2 pos)
    : Item(pos)
{
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Coin::Blinking::blinking_, 1 / 6.0f);
}

void Coin::Update_()
{
    appear_animation = 0;
    animation_.Update(GetFrameTime());
}

void Coin::Activate_(Player &player, PlayerInformation &info)
{
    info.UpdateCoins(1);
    is_delete = 1;
    SoundManager::GetInstance().PlaySoundEffect("coin");
}

bool Coin::Can_Move() const { return false; }