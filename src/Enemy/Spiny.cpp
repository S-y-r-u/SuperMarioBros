#include "Enemy/Spiny.h"

Spiny::Spiny(Vector2 pos, Vector2 velo, float gravity)
    : Enemy(pos, velo, gravity),
      state_(Spiny_State::egg),
      m_egg(Enemies_Sprite::Spiny::Egg::egg_),
      m_normal(Enemies_Sprite::Spiny::Normal::normal_),
      is_jump(false)
{
    rec_ = m_egg[current_frame];
}

void Spiny::Update(float dt)
{
    previous_frame_pos = position_;

    if (state_ != Spiny_State::be_fired_or_hit)
    {
        if (!is_ground || is_jump)
            velocity_.y += Physics::gravity_ * dt;
    }

    position_.y += velocity_.y * dt;

    if (state_ != Spiny_State::be_fired_or_hit)
        Move_(dt);

    if (state_ == Spiny_State::be_fired_or_hit && position_.y - rec_.height >= Screen_h)
        is_active = false;

    Animate_();
}

void Spiny::Draw() const
{
    Rectangle src = rec_;
    src.width = (velocity_.x < 0) ? std::abs(src.width) : -std::abs(src.width);

    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src.width) * scale_screen,
        src.height * scale_screen};

    DrawTexturePro(sprite_.sprite, src, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

Vector2 Spiny::Get_Previous_Pos() const { return previous_frame_pos; }

void Spiny::Notify_Fall(float dt)
{
    if (is_ground && state_ != Spiny_State::be_fired_or_hit)
    {
        is_ground = false;
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
        frame_timer = 0.0f;
        current_frame = 0;
        rec_ = m_normal[current_frame];
    }
}

void Spiny::Notify_Jump()
{
    if (state_ == Spiny_State::normal)
    {
        is_jump = true;
        is_ground = false;
        velocity_.y = -Jump_Velocity; // vận tốc nhảy lên, có thể điều chỉnh
    }
}

void Spiny::Notify_Be_Fired_Or_Hit(PlayerInformation &info)
{
    if (state_ == Spiny_State::normal)
    {
        info.UpdateScore(Score_Spiny);
        state_ = Spiny_State::be_fired_or_hit;
        rec_ = Enemies_Sprite::Spiny::be_fired_or_hit;
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, Score_Spiny);
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

    frame_timer += GetFrameTime();

    if (state_ == Spiny_State::egg && frame_timer >= animation_speed * 0.75f)
    {
        frame_timer = 0;
        current_frame = (current_frame + 1) % m_egg.size();
        rec_ = m_egg[current_frame];
    }
    else if (state_ == Spiny_State::normal && frame_timer >= animation_speed)
    {
        frame_timer = 0;
        current_frame = (current_frame + 1) % m_normal.size();
        rec_ = m_normal[current_frame];
    }
}

void Spiny::Move_(float dt)
{
    position_.x += velocity_.x * dt;

    if (position_.x - rec_.width / 2.0f <= 0.0f || position_.x + rec_.width / 2.0f >= 214 * 48.0f)
    {
        position_.x = Clamp(position_.x, rec_.width / 2.0f, 214 * 48.0f - rec_.width / 2.0f);
        velocity_.x *= -1;
    }
}
