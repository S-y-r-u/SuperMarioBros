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

json Coin::to_json() const {
    json j;
    j["type"] = "coin" ; // hoặc lưu type khác nếu cần
    //item
    j["pos"] = { pos_.x, pos_.y };
    j["appear_animation"] = appear_animation;
    j["is_delete"] = is_delete;
    j["animation"] = animation_.to_json();
    return j;
}

void Coin::from_json(const json& j) {
    pos_ = { j["pos"][0].get<float>(), j["pos"][1].get<float>() };
    appear_animation = j["appear_animation"].get<int>();
    is_delete = j["is_delete"].get<bool>();
    animation_.from_json(j["animation"]);
}
