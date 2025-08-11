#include "Item/HiddenCoin.h"

HiddenCoin::HiddenCoin(Vector2 pos)
    : Item(pos),
      velocity_({0.0f, -Push_Height}),
      before_pos_(pos),
      timer_(0.0f)
{

    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Coin::Hidden::hidden_, 1 / 6.0f);
    const float gravity = Physics::gravity_;                       // 1000.0f
    const float total_air_time = 2 * Push_Height / gravity * 0.8f; // 1.0f

    sprite_interval_ = total_air_time / static_cast<float>(animation_.Get_Frame_Count());
    animation_.Set_Frame_Speed(sprite_interval_);
}

void HiddenCoin::Update_()
{
    Appear_();
}

void HiddenCoin::Appear_()
{
    const float gravity = Physics::gravity_;
    timer_ += GetFrameTime();

    // Cập nhật animation theo thời gian
    animation_.Update(GetFrameTime());

    if(timer_ >= sprite_interval_ * animation_.Get_Frame_Count() - GetFrameTime())
    {
        is_delete = true;
    }

    // Physics
    velocity_.y += gravity * GetFrameTime();
    pos_.y += velocity_.y * GetFrameTime();

    if (pos_.y >= before_pos_.y)
    {
        pos_.y = before_pos_.y;
        is_delete = true;
    }
}

void HiddenCoin::Activate_(Player &player, PlayerInformation &info)
{
    player.collectCoin();
    info.UpdateCoins(1);
}

bool HiddenCoin::Can_Move() const
{
    return false;
}
