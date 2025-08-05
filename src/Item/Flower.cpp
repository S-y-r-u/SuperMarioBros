#include "Item/Flower.h"

Flower::Flower(Vector2 pos)
    : Item(pos), 
    is_appear(0), 
    before_pos(pos)
{
    rec_ = Item_Sprite::Flower::fire_flower;
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
