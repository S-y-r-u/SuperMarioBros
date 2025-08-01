#include "Enemy/KoopaTroopaState.h"
#include "Enemy/KoopaTroopa.h"

// Common function 
void KoopaState::OnFired(KoopaTroopa* koopa) {
    koopa->SetState(new KoopaDyingState());
}

// ---------- WALKING ----------
void KoopaWalkingState::Enter(KoopaTroopa* koopa) {
    koopa->rec_ = koopa->walking_frames_[0];
    koopa->velocity_.x = 30.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->frame_timer = 0;
    koopa->current_frame = 0;
}

void KoopaWalkingState::Update(KoopaTroopa* koopa, float dt) {
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
    // std::cout << koopa->velocity_.y << std::endl;
    koopa->frame_timer ++;
    if (koopa->frame_timer >= 12) {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->walking_frames_.size();
        koopa->rec_ = koopa->walking_frames_[koopa->current_frame];
        koopa->frame_timer = 0;
    }
}

void KoopaWalkingState::OnStomped(KoopaTroopa* koopa) {
    koopa->SetState(new KoopaShellIdleState());
}

// ---------- SHELL IDLE ----------
void KoopaShellIdleState::Enter(KoopaTroopa* koopa) {
    koopa->rec_ = koopa->shell_idle_frames_[0];
    koopa->velocity_.y = 100.f; // dừng lại
    koopa->velocity_.x = 0;
    koopa->current_frame = 0;
    koopa->frame_timer = 0;
}

void KoopaShellIdleState::Update(KoopaTroopa* koopa, float dt) {
    if (koopa->is_ground){
        koopa->velocity_.y = 0;
        koopa->is_ground = false; // reset ground state
    }
    koopa->frame_timer ++;
    if (koopa->frame_timer >= 180 && koopa->frame_timer < 300) {
        koopa->current_frame = 1; // Chuyển sang frame 2 sau 2 giây
        koopa->rec_ = koopa->shell_idle_frames_[koopa->current_frame];
    }
    else if (koopa->frame_timer >= 300) {
        koopa->SetState(new KoopaWalkingState());
    }
}

void KoopaShellIdleState::OnStomped(KoopaTroopa* koopa) {
    koopa->SetState(new KoopaShellMovingState());
}

// ---------- SHELL MOVING ----------
void KoopaShellMovingState::Enter(KoopaTroopa* koopa) {
    koopa->rec_ = koopa->shell_moving_frames_[0];
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 500.0f : -500.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->current_frame = 0;
    koopa->frame_timer = 0;
}

void KoopaShellMovingState::Update(KoopaTroopa* koopa, float dt) {
    koopa->frame_timer ++;
    if (koopa->frame_timer >= 12) {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->shell_moving_frames_.size();
        koopa->rec_ = koopa->shell_moving_frames_[koopa->current_frame];
        koopa->frame_timer = 0;
    }
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
}

void KoopaShellMovingState::OnStomped(KoopaTroopa* koopa) {
    // đá lại thì dừng
    koopa->SetState(new KoopaShellIdleState());
}

// ---------- DYING ----------
void KoopaDyingState::Enter(KoopaTroopa* koopa) {
    koopa->rec_ = koopa->be_dying_frame_;
    koopa->velocity_.x = 0;
    koopa->velocity_.y = -800.0f; //upward movement
    koopa->is_dead = true;
}

void KoopaDyingState::Update(KoopaTroopa* koopa, float dt) {
    // gravity đã xử lý ngoài

    if (dying_up_timer > 0.0f) dying_up_timer -= dt;
    if (dying_up_timer <= 0.0f) dying_down_timer -= dt;
    if (dying_down_timer <= 0.0f) {
        koopa->is_active = false;
    }
    if (dying_up_timer > 0.0f) {
        koopa->velocity_.y = -800.0f; // upward movement
    }
    else if (dying_up_timer <= 0.0f) {
        koopa->velocity_.y = 800.0f; // downward movement
    }
}

//_______Flying _______________
void KoopaFlyingState::Enter(KoopaTroopa* koopa) {
    koopa->rec_ = koopa->flying_frames_[0];
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 50.0f : -50.0f;
    koopa->velocity_.y = -50.0f; // bay lên ban đầu
    koopa->current_frame = 0;
    koopa->frame_timer = 0;
    fly_timer = 0;
}

void KoopaFlyingState::Update(KoopaTroopa* koopa, float dt) {
    fly_timer += dt;
    if (koopa->is_ground) {
        koopa->velocity_.y = -fly_speed; // nếu chạm đất thì bay lên
        koopa->is_ground = false; // không còn trên mặt đất
    }
    koopa->velocity_.y += koopa->gravity_ * dt; // áp dụng trọng lực

    if (fly_timer >= fly_interval) {
        koopa->velocity_.x *= -1; // đổi hướng bay left right
        fly_timer = 0;
    }

    koopa->frame_timer ++;
    if (koopa->frame_timer >= 30) {
        koopa->current_frame = (koopa->current_frame + 1) % koopa->flying_frames_.size();
        koopa->frame_timer = 0;
        koopa->rec_ = koopa->flying_frames_[koopa->current_frame];
    }
}

void KoopaFlyingState::OnStomped(KoopaTroopa* koopa) {
    // Khi bị giẫm sẽ thành shell
    koopa->SetState(new KoopaShellIdleState());
}
