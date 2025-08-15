#include "Enemy/Spiny.h"

Spiny::Spiny(Vector2 pos, Vector2 velo)
    : Enemy(pos, velo, 0.0f),
      state_(Spiny_State::egg),
      is_jump(false)
{
    score = 100;
    animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Spiny::Egg::egg_, 1 / 10.0f);
}

void Spiny::Update(float dt)
{
    previous_frame_pos = position_;
    if (!is_ground || is_jump)
        velocity_.y += Physics::gravity_ * dt;

    position_.y += velocity_.y * dt;

    if (state_ != Spiny_State::be_fired_or_hit)
        Move_(dt);

    if (state_ == Spiny_State::be_fired_or_hit && position_.y - animation_.Get_Current_Rec().height >= Screen_h)
        is_active = false;

    Animate_();
}

void Spiny::Draw() const
{
    Rectangle src = animation_.Get_Current_Rec();
    src.width = (velocity_.x < 0) ? std::abs(src.width) : -std::abs(src.width);

    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src.width) * scale_screen,
        src.height * scale_screen};

    DrawTexturePro(animation_.Get_Sprite().sprite, src, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

Vector2 Spiny::Get_Previous_Pos() const { return previous_frame_pos; }

void Spiny::Notify_Fall(float dt)
{
    if (is_ground && state_ != Spiny_State::be_fired_or_hit)
    {
        prev_ground = true;
        is_ground = false;
    }
    else if (!is_ground && state_ != Spiny_State::be_fired_or_hit)
    {
        prev_ground = false;
    }
}

void Spiny::Notify_On_Ground()
{
    if (state_ == Spiny_State::be_fired_or_hit)
        return;

    is_ground = true;
    is_jump = false;
    velocity_.y = 0.0f;

    if (state_ == Spiny_State::egg)
    {
        state_ = Spiny_State::normal;
        animation_.Set_Frames(Enemies_Sprite::Spiny::Normal::normal_);
        animation_.Set_Frame_Speed(1 / 6.0f);
    }
}

void Spiny::Notify_Jump()
{
    if (state_ == Spiny_State::normal || state_ == Spiny_State::egg)
    {
        is_jump = true;
        is_ground = false;
        velocity_.y = -Jump_Velocity; // vận tốc nhảy lên, có thể điều chỉnh
    }
}

void Spiny::Notify_Be_Fired_Or_Hit()
{
    if (state_ == Spiny_State::normal)
    {
        state_ = Spiny_State::be_fired_or_hit;
        animation_.Set_Rec(Enemies_Sprite::Spiny::be_fired_or_hit);
        is_dead = true;
        is_ground = false;
        velocity_.y = -Push_Velocity;
    }
}

void Spiny::Set_Pos(Vector2 pos)
{
    if (state_ != Spiny_State::be_fired_or_hit)
        position_ = pos;
}

bool Spiny::Can_Be_Stomped() const { return false; }

bool Spiny::Can_Be_Fired_Or_Hit() const { return true; }

bool Spiny::Can_Jump() const { return true; }

void Spiny::Animate_()
{
    if (state_ == Spiny_State::be_fired_or_hit)
        return;

    animation_.Update(GetFrameTime());
}

void Spiny::Move_(float dt)
{
    position_.x += velocity_.x * dt;
}

void Spiny::Collision_With_Other_Enemy(Enemy *other)
{
    Enemy::Collision_With_Other_Enemy(other);
    if (state_ == Spiny_State::egg)
    {
        Notify_Jump();
    }
    else if ((!is_ground && !prev_ground) || is_jump)
    {
        Notify_Jump();
    }
}


json Spiny::to_json() const {
    json j;

    // Thuộc tính kế thừa từ Enemy
    j["position"] = { position_.x, position_.y };
    j["velocity"] = { velocity_.x, velocity_.y };
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;

    // Thuộc tính riêng của Spiny
    j["state"] = static_cast<int>(state_);
    j["previous_frame_pos"] = { previous_frame_pos.x, previous_frame_pos.y };
    j["is_jump"] = is_jump;
    j["prev_ground"] = prev_ground;

    return j;
}

void Spiny::from_json(const json& j) {
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

    // Thuộc tính riêng của Spiny
    state_ = static_cast<Spiny_State>(j.at("state").get<int>());
    previous_frame_pos.x = j.at("previous_frame_pos")[0];
    previous_frame_pos.y = j.at("previous_frame_pos")[1];
    is_jump = j.at("is_jump");
    prev_ground = j.at("prev_ground");
}