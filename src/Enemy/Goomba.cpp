#include "Enemy/Goomba.h"

Goomba::Goomba(Vector2 pos)
    : Enemy(pos, Vector2{75.0f, 0.0f}, 0.0f),
      state_(Goomba_State::normal),
      m_normal(Enemies_Sprite::Goomba_Brown::Normal::normal_),
      stomped_timer(0.0f)
{
    rec_ = m_normal[current_frame];
}

void Goomba::Draw() const
{
    Rectangle dest_rec = {position_.x, position_.y, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(sprite_.sprite, rec_, dest_rec,
                   {rec_.width * scale_screen / 2.0f, rec_.height * scale_screen},
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

    if (position_.y - rec_.height >= Screen_h)
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
        rec_ = Enemies_Sprite::Goomba_Brown::be_stomped;
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
        rec_ = Enemies_Sprite::Goomba_Brown::be_fired_or_hit;
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

    if (position_.x + rec_.width / 2.0f <= 0.0f || position_.x + rec_.width / 2.0f >= 214 * 48.0f)
    {
        position_.x = Clamp(position_.x, rec_.width / 2.0f, 214 * 48.0f - rec_.width / 2.0f);
        velocity_.x *= -1;
    }
}

void Goomba::Animate_()
{
    if (state_ == Goomba_State::normal)
    {
        frame_timer += GetFrameTime();
        if (frame_timer >= animation_speed)
        {
            current_frame = (current_frame + 1) % m_normal.size();
            frame_timer = 0.0f;
        }
        rec_ = m_normal[current_frame];
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
