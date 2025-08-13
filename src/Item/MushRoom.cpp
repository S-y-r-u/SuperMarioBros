#include "Item/MushRoom.h"
#include <iostream>

Mush_Room::Mush_Room(Vector2 pos, State_MushRoom state)
    : Item(pos),
      state_(state),
      direct_(1),
      fall_(false),
      is_appear(false),
      jump_(true),
      before_pos_({pos.x, pos.y - Tile_Size})
{
    velocity_ = {0.0f, 0.0f};
    previous_frame_pos = pos_;

    switch (state_)
    {
    case State_MushRoom::super_:
        animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Mushroom::super_mushroom);
        break;
    case State_MushRoom::one_up:
        animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Mushroom::one_up_mushroom);
        break;
    case State_MushRoom::posion_:
        animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Mushroom::posion_mushroom);
        break;
    default:
        break;
    }
}

void Mush_Room::Notify_Fall()
{
    if (!jump_ && !fall_)
    {
        fall_ = true;
        velocity_.y = 0.0f; // bắt đầu rơi từ vận tốc đứng yên
    }
}

void Mush_Room::Notify_On_Ground()
{
    fall_ = false;
    jump_ = false;
    velocity_.y = 0.0f;
}

void Mush_Room::Notify_Change_Direct() { direct_ = !direct_; }

void Mush_Room::Notify_Jump()
{
    jump_ = true;
    fall_ = false;
    velocity_.y = -Mushroom_Ini_Velo;
}

void Mush_Room::Jump_()
{
    if (!is_appear || !jump_)
        return;

    float dt = GetFrameTime();
    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;

    float move = Mush_Room_And_Star_Speed * dt;
    pos_.x += direct_ ? move : -move;
}

void Mush_Room::Fall_()
{
    if (!is_appear || !fall_)
        return;

    float dt = GetFrameTime();
    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;
}

void Mush_Room::Move_()
{
    if (!is_appear || fall_ || jump_)
        return;

    // Thiết lập tốc độ ngang, không ảnh hưởng dọc
    velocity_.x = (direct_ ? 1 : -1) * Mush_Room_And_Star_Speed;
    velocity_.y = 0.0f;

    pos_.x += velocity_.x * GetFrameTime();
}

void Mush_Room::Appear_()
{
    if (is_appear)
        return;

    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos_.y)
    {
        appear_animation = 0;
        is_appear = true;
        pos_.y = before_pos_.y;
        previous_frame_pos = pos_;
    }
}

void Mush_Room::Be_Delete()
{
    if (pos_.y - animation_.Get_Current_Rec().height * scale_screen >= Screen_h)
        is_delete = true;
}

void Mush_Room::Update_()
{
    previous_frame_pos = pos_;
    Appear_();
    Move_();
    Fall_();
    Jump_();
    Be_Delete();
}

void Mush_Room::Activate_(Player &player, PlayerInformation &info)
{
    if (state_ == State_MushRoom::super_)
    {
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore(player.getPosition(), Score_One_Up_Super);
        player.getMushroom();
    }
    info.UpdateScore(Score_One_Up_Super);
    SoundManager::GetInstance().PlaySoundEffect("powerup");
    is_delete = true;
}

Vector2 Mush_Room::Get_Previous_Frame_Pos() { return previous_frame_pos; }

bool Mush_Room::Get_Direct() const { return direct_; }

bool Mush_Room::Can_Move() const { return true; }

json Mush_Room::to_json() const {
    json j;
    j["type"] = "super_mushroom" ; // hoặc lưu type khác nếu cần
    //item
    j["pos"] = { pos_.x, pos_.y };
    j["appear_animation"] = appear_animation;
    j["is_delete"] = is_delete;
    j["animation"] = animation_.to_json();

    //mushroom
    j["state"] = static_cast<int>(state_);
    j["direction"] = direct_;
    j["falling"] = fall_;
    j["appearing"] = is_appear;
    j["jumping"] = jump_;
    j["velocity"] = { velocity_.x, velocity_.y };
    j["previous_frame_pos"] = { previous_frame_pos.x, previous_frame_pos.y };
    j["before_pos"] = { before_pos_.x, before_pos_.y };
    return j;
}

void Mush_Room::from_json(const json& j) {
    pos_ = { j["pos"][0].get<float>(), j["pos"][1].get<float>() };
    appear_animation = j["appear_animation"].get<int>();
    is_delete = j["is_delete"].get<bool>();
    animation_.from_json(j["animation"]);

    // mushroom
    state_ = static_cast<State_MushRoom>(j["state"].get<int>());
    direct_ = j["direction"].get<bool>();
    fall_ = j["falling"].get<bool>();
    is_appear = j["appearing"].get<bool>();
    jump_ = j["jumping"].get<bool>();
    velocity_ = { j["velocity"][0].get<float>(), j["velocity"][1].get<float>() };
    previous_frame_pos = { j["previous_frame_pos"][0].get<float>(), j["previous_frame_pos"][1].get<float>() };
    before_pos_ = { j["before_pos"][0].get<float>(), j["before_pos"][1].get<float>() };
}
