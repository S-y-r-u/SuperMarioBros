#include "Enemy/Goomba.h"

Goomba::Goomba(Vector2 pos)
    : Enemy(pos, Vector2{-75.0f, 0.0f}, 0.0f),
      state_(Goomba_State::normal),
      stomped_timer(0.0f),
      previous_frame_pos(pos)
{
    animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Goomba_Brown::Normal::normal_, 1 / 6.0f);
}

void Goomba::Draw() const
{
    Rectangle dest_rec = {position_.x, position_.y, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec,
                   {animation_.Get_Current_Rec().width * scale_screen / 2.0f, animation_.Get_Current_Rec().height * scale_screen},
                   0.0f, WHITE);
}

void Goomba::Update(float dt)
{
    previous_frame_pos = position_;

    if (!is_ground && state_ == Goomba_State::normal)
        velocity_.y += Physics::gravity_ * dt;

    if (state_ == Goomba_State::be_fired_or_hit)
        Be_Fired_Or_Hit(dt);

    position_.y += velocity_.y * dt;

    if (state_ == Goomba_State::normal)
        Move_(dt);

    Be_Stomped();
    Animate_();

    if (position_.y - animation_.Get_Current_Rec().height >= Screen_h)
        is_active = false;
}

bool Goomba::Can_Be_Stomped() const { return true; }

bool Goomba::Can_Be_Fired_Or_Hit() const { return true; }

Vector2 Goomba::Get_Previous_Pos() const { return previous_frame_pos; }

void Goomba::Notify_Fall(float dt)
{
    if (is_ground && state_ == Goomba_State::normal)
    {
        is_ground = false;
    }
}

void Goomba::Notify_On_Ground()
{
    if (state_ == Goomba_State::normal)
    {
        is_ground = true;
        velocity_.y = 0.0f;
    }
}

void Goomba::Notify_Be_Stomped(PlayerInformation &info)
{
    if (state_ == Goomba_State::normal)
    {
        info.UpdateScore(Score_Goomba);
        state_ = Goomba_State::be_stomped;
        animation_.Set_Rec(Enemies_Sprite::Goomba_Brown::be_stomped);
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, Score_Goomba);
        is_dead = true;
        velocity_.y = 0.0f;
    }
}

void Goomba::Notify_Be_Fired_Or_Hit(PlayerInformation &info)
{
    if (state_ == Goomba_State::normal)
    {
        info.UpdateScore(Score_Goomba);
        state_ = Goomba_State::be_fired_or_hit;
        animation_.Set_Rec(Enemies_Sprite::Goomba_Brown::be_fired_or_hit);
        velocity_.y = -Push_Velocity; // Nhảy lên
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, Score_Goomba);
        is_dead = true;
        is_ground = false;
    }
}

void Goomba::Set_Pos(Vector2 pos)
{
    if (state_ == Goomba_State::normal)
    {
        position_ = pos;
    }
}

void Goomba::Move_(float dt)
{
    position_.x += velocity_.x * dt;
}

void Goomba::Animate_()
{
    if (state_ == Goomba_State::normal)
    {
        animation_.Update(GetFrameTime());
    }
}

void Goomba::Be_Stomped()
{
    if (state_ == Goomba_State::be_stomped)
    {
        stomped_timer += GetFrameTime();
        if (stomped_timer >= Stomped_Duration)
        {
            is_active = false;
        }
    }
}

void Goomba::Be_Fired_Or_Hit(float dt)
{
    velocity_.y += Physics::gravity_ * dt;
}


json Goomba::to_json() const {
    json j;

    // Thuộc tính kế thừa từ Enemy
    j["position"] = { position_.x, position_.y };
    j["velocity"] = { velocity_.x, velocity_.y };
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;

    // Thuộc tính của Goomba
    j["state"] = static_cast<int>(state_);
    j["previous_frame_pos"] = { previous_frame_pos.x, previous_frame_pos.y };
    j["stomped_timer"] = stomped_timer;

    return j;
}

void Goomba::from_json(const json& j) {
    // Thuộc tính kế thừa từ Enemy
    position_.x = j.at("position")[0];
    position_.y = j.at("position")[1];
    velocity_.x = j.at("velocity")[0];
    velocity_.y = j.at("velocity")[1];
    gravity_ = j.at("gravity");
    is_ground = j.at("is_ground");
    is_active = j.at("is_active");
    is_dead = j.at("is_dead");
    first_appear = j.at("first_appear");

    // Thuộc tính của Goomba
    state_ = static_cast<Goomba_State>(j.at("state").get<int>());
    previous_frame_pos.x = j.at("previous_frame_pos")[0];
    previous_frame_pos.y = j.at("previous_frame_pos")[1];
    stomped_timer = j.at("stomped_timer");
}