#include "Item/Star.h"
#include <iostream>

Star::Star(Vector2 pos)
    : Item(pos),
      direct_(true),
      is_appear(false),
      before_pos(pos),
      velocity_({0.0f, -Star_Ini_Velo}),
      previous_frame_pos(pos)
{
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Star::invincible_star);
}

void Star::Notify_On_Ground()
{
    if (velocity_.y != -Star_Ini_Velo)
    {
        velocity_.y = -Star_Ini_Velo;
        before_pos = pos_;
    }
}

void Star::Notify_Change_Direct()
{
    direct_ = !direct_;
}

void Star::Fall_(float dt)
{
    if (!is_appear)
        return;

    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;
}

void Star::Move_(float dt)
{
    if (!is_appear)
        return;

    float speed = Mush_Room_And_Star_Speed * dt;
    if (direct_)
        pos_.x += speed;
    else
        pos_.x -= speed;
}

void Star::Appear_()
{
    if (is_appear)
        return;

    pos_.y -= Appear_Animation;

    if (pos_.y <= before_pos.y - Tile_Size)
    {
        appear_animation = false;
        is_appear = true;
        pos_.y = before_pos.y - Tile_Size;
        before_pos = pos_;
        previous_frame_pos = pos_;

        // Bắt đầu nhảy lên
        velocity_.y = -Star_Ini_Velo;
    }
}

void Star::Be_Delete()
{
    if (pos_.y - animation_.Get_Current_Rec().height * scale_screen >= Screen_h)
        is_delete = true;
}

void Star::Update_()
{
    float dt = GetFrameTime();
    previous_frame_pos = pos_;

    Appear_();
    Move_(dt);
    Fall_(dt);
    Be_Delete();
}

void Star::Activate_(Player &player, PlayerInformation &info)
{
    Score_Manager &score_manager = Score_Manager::GetInstance();
    score_manager.AddScore({player.getPosition().x + player.get_draw_rec().width, player.getPosition().y}, Score_Star);
    player.getStar();
    info.UpdateScore(Score_Star);
    SoundManager::GetInstance().PlaySoundEffect("powerup");
    is_delete = true;
}

Vector2 Star::Get_Previous_Frame_Pos()
{
    return previous_frame_pos;
}

bool Star::Get_Direct() const
{
    return direct_;
}

bool Star::Can_Move() const
{
    return true;
}

json Star::to_json() const {
    json j;
    j["type"] = "star" ; // hoặc lưu type khác nếu cần
    //item
    j["pos"] = { pos_.x, pos_.y };
    j["appear_animation"] = appear_animation;
    j["is_delete"] = is_delete;

    //star 
    j["direction"] = direct_;
    j["is_appear"] = is_appear;
    j["before_pos"] = { before_pos.x, before_pos.y };
    j["velocity"] = { velocity_.x, velocity_.y };
    return j;
}

void Star::from_json(const json& j) {
    pos_ = { j["pos"][0].get<float>(), j["pos"][1].get<float>() };
    appear_animation = j["appear_animation"].get<int>();
    is_delete = j["is_delete"].get<bool>();

    //star
    direct_ = j["direction"].get<bool>();
    is_appear = j["is_appear"].get<bool>();
    before_pos = { j["before_pos"][0].get<float>(), j["before_pos"][1].get<float>() };
    velocity_ = { j["velocity"][0].get<float>(), j["velocity"][1].get<float>() };
}
