#include "Enemy/KoopaTroopaState.h"
#include "Enemy/KoopaTroopa.h"

// Common function
void KoopaState::OnFired(KoopaTroopa *koopa)
{
    koopa->SetState(new KoopaDyingState());
}

// ---------- WALKING ----------
void KoopaWalkingState::Enter(KoopaTroopa *koopa)
{
    koopa->rec_ = koopa->walking_frames_[0];
    koopa->velocity_.x = 75.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->gravity_ = 1000.0f;
    koopa->frame_timer = 0.0f;
    koopa->current_frame = 0;
}

void KoopaWalkingState::Update(KoopaTroopa *koopa, float dt)
{
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
    // std::cout << koopa->velocity_.y << std::endl;
    koopa->frame_timer += dt;
    if (koopa->frame_timer >= koopa->animation_speed)
    {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->walking_frames_.size();
        koopa->rec_ = koopa->walking_frames_[koopa->current_frame];
        koopa->frame_timer = 0.0f;
    }
}

void KoopaWalkingState::OnStomped(KoopaTroopa *koopa)
{
    koopa->SetState(new KoopaShellIdleState());
}

// ---------- SHELL IDLE ----------
void KoopaShellIdleState::Enter(KoopaTroopa *koopa)
{
    koopa->rec_ = koopa->shell_idle_frames_[0];
    koopa->velocity_.y = -100.f; // dừng lại
    koopa->velocity_.x = 0;
    koopa->current_frame = 0;
    koopa->frame_timer = 0.0f;
}

void KoopaShellIdleState::Update(KoopaTroopa *koopa, float dt)
{
    koopa->frame_timer += dt;

    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity

    if (koopa->frame_timer >= 3.0f && koopa->frame_timer < 5.0f)
    {
        koopa->current_frame = 1; // Chuyển sang frame 2 sau 2 giây
        koopa->rec_ = koopa->shell_idle_frames_[koopa->current_frame];
    }
    else if (koopa->frame_timer >= 5.0f)
    {
        koopa->SetState(new KoopaWalkingState());
    }
}

void KoopaShellIdleState::OnStomped(KoopaTroopa *koopa)
{
    koopa->SetState(new KoopaShellMovingState());
}

// ---------- SHELL MOVING ----------
void KoopaShellMovingState::Enter(KoopaTroopa *koopa)
{
    koopa->rec_ = koopa->shell_moving_frames_[0];
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 900.0f : -900.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->current_frame = 0;
    koopa->frame_timer = 0;
}

void KoopaShellMovingState::Update(KoopaTroopa *koopa, float dt)
{
    koopa->frame_timer += dt;
    if (koopa->frame_timer >= koopa->animation_speed)
    {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->shell_moving_frames_.size();
        koopa->rec_ = koopa->shell_moving_frames_[koopa->current_frame];
        koopa->frame_timer = 0.0f;
    }
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
}

void KoopaShellMovingState::OnStomped(KoopaTroopa *koopa)
{
    // đá lại thì dừng
    koopa->SetState(new KoopaShellIdleState());
}

// ---------- DYING ----------
void KoopaDyingState::Enter(KoopaTroopa *koopa)
{
    koopa->rec_ = koopa->be_dying_frame_;
    koopa->velocity_.x = 0;
    koopa->velocity_.y = -200.0f; // upward movement
    koopa->is_dead = true;
    koopa->gravity_ = 1000.0f;
    if (koopa->previous_state && dynamic_cast<KoopaFlyingState *>(koopa->previous_state))
    {
        score_ = Score_Dying_Flying;
    }
    else if (koopa->previous_state && dynamic_cast<KoopaWalkingState *>(koopa->previous_state))
    {
        score_ = Score_Dying_Walking;
    }
    else if (koopa->previous_state && dynamic_cast<KoopaShellIdleState *>(koopa->previous_state))
    {
        score_ = Score_Dying_Shell;
    }
}

void KoopaDyingState::Update(KoopaTroopa *koopa, float dt)
{
    // gravity đã xử lý ngoài

    koopa->velocity_.y += koopa->gravity_ * dt;
    if (koopa->position_.y >= Screen_h * scale_screen)
    {
        koopa->is_active = false;
    }
}

//_______Flying _______________
void KoopaFlyingState::Enter(KoopaTroopa *koopa)
{
    koopa->rec_ = koopa->flying_frames_[0];
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 90.0f : -90.0f;
    koopa->velocity_.y = -fly_speed; // bay lên ban đầu
    koopa->gravity_ = 600.0f;
    koopa->current_frame = 0;
    koopa->frame_timer = 0.0f;
    fly_timer = 0.0f;
}

void KoopaFlyingState::Update(KoopaTroopa *koopa, float dt)
{
    fly_timer += dt;
    if (koopa->is_ground)
    {
        koopa->velocity_.y = -fly_speed; // nếu chạm đất thì bay lên
        koopa->is_ground = false;        // không còn trên mặt đất
    }
    koopa->velocity_.y += koopa->gravity_ * dt; // áp dụng trọng lực

    if (fly_timer >= fly_interval)
    {
        koopa->velocity_.x *= -1; // đổi hướng bay left right
        fly_timer = 0;
    }

    koopa->frame_timer += dt;
    if (koopa->frame_timer >= 0.5f)
    {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->flying_frames_.size();
        koopa->frame_timer = 0.0f;
        koopa->rec_ = koopa->flying_frames_[koopa->current_frame];
    }
}

void KoopaFlyingState::OnStomped(KoopaTroopa *koopa)
{
    // Khi bị giẫm sẽ thành shell
    koopa->SetState(new KoopaWalkingState());
}
