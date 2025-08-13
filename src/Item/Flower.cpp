#include "Item/Flower.h"

Flower::Flower(Vector2 pos)
    : Item(pos), 
    is_appear(0), 
    before_pos(pos)
{
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Flower::fire_flower);
}

void Flower::Update_()
{
    Appear_();
}

void Flower::Activate_(Player &player, PlayerInformation &info)
{
    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.AddScore({player.getPosition().x + player.get_draw_rec().width, player.getPosition().y}, Score_Flower);
    player.getFlower();
    info.UpdateScore(Score_Flower);
    is_delete = 1;
    SoundManager::GetInstance().PlaySoundEffect("powerup");
}

void Flower::Appear_()
{
    if (is_appear)
        return;
    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos.y - Tile_Size)
    {
        is_appear = 1;
        appear_animation = 0;
        pos_.y = before_pos.y - Tile_Size;
    }
}

bool Flower::Can_Move() const { return false; }


json Flower::to_json() const {
    json j;
    j["type"] = "flower" ; // hoặc lưu type khác nếu cần
    //item
    j["pos"] = { pos_.x, pos_.y };
    j["appear_animation"] = appear_animation;
    j["is_delete"] = is_delete;

    //flower
    j["before_pos"] = { before_pos.x, before_pos.y };
    j["is_appear"] = is_appear;

    return j;
}

void Flower::from_json(const json& j) {
    pos_ = { j["pos"][0].get<float>(), j["pos"][1].get<float>() };
    appear_animation = j["appear_animation"].get<int>();
    is_delete = j["is_delete"].get<bool>();

    //flower
    before_pos = { j["before_pos"][0].get<float>(), j["before_pos"][1].get<float>() };
    is_appear = j["is_appear"].get<bool>();

}
