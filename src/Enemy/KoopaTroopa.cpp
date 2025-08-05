#include "Enemy\KoopaTroopa.h"
#include "Enemy\KoopaTroopaState.h"

KoopaTroopa::KoopaTroopa(Vector2 pos)
    : Enemy(pos, {75.0f, 0}, 1000.0f),
      current_state_(nullptr),
      previous_state(nullptr),
      before_pos_(pos)
{
    SetState(new KoopaWalkingState());
}

// Constructor cho flying koopa
KoopaTroopa::KoopaTroopa(Vector2 pos, bool is_flying)
    : Enemy(pos, {120.0f, 0}, 1000.0f),
      current_state_(nullptr),
      previous_state(nullptr),
      before_pos_(pos)
{
    if (is_flying)
    {
        SetState(new KoopaFlyingState());
    }
    else
    {
        SetState(new KoopaWalkingState());
    }
}

KoopaTroopa::~KoopaTroopa()
{
    delete previous_state;
    delete current_state_;
}

void KoopaTroopa::SetState(KoopaState *new_state)
{
    if (current_state_)
        current_state_->Exit(this);
    delete previous_state;
    previous_state = current_state_;
    current_state_ = new_state;
    if (current_state_)
        current_state_->Enter(this);
}

void KoopaTroopa::Notify_Fall(float dt)
{

    if (current_state_)
    {
        current_state_->Update(this, dt);
    }
}

void KoopaTroopa::Update(float dt)
{
    if (!is_active)
        return;
    // Apply velocity to position
    if (is_dead)
    {
        if (current_state_)
            current_state_->Update(this, dt);
    }
    before_pos_ = position_; // Lưu vị trí trước khi cập nhật
    position_ = Vector2Add(position_, Vector2Scale(velocity_, dt));
    if (position_.x - rec_.width / 2.0f < 0 || position_.x + rec_.width / 2.0f > 214 * 48.0f)
    {
        // Nếu ra ngoài biên, dừng lại
        position_.x = Clamp(position_.x, rec_.width / 2.0f, 214 * 48.0f - rec_.width / 2.0f);
        velocity_.x *= -1.0f;
    }
}

void KoopaTroopa::Draw() const
{
    bool flip = velocity_.x >= 0;
    Rectangle rec__ = {rec_.x, rec_.y, flip ? -1.0f * rec_.width : rec_.width, rec_.height};
    float draw_width = rec_.width * scale_screen;
    float draw_height = rec_.height * scale_screen;
    Rectangle dest_rec = {position_.x, position_.y, draw_width, draw_height};
    Vector2 origin = {draw_width / 2.0f, draw_height};
    DrawTexturePro(sprite_.sprite, rec__, dest_rec,
                   {origin.x, origin.y}, // Điểm neo ở giữa
                   0.0f, WHITE);
}

void KoopaTroopa::Notify_Be_Stomped(PlayerInformation &info)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    if (current_state_)
    {
        current_state_->OnStomped(this, info);
        info.UpdateScore(current_state_->Get_Score());
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, current_state_->Get_Score());
    }
}

void KoopaTroopa::Notify_Be_Fired_Or_Hit(PlayerInformation &info)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    if (current_state_)
    {
        current_state_->OnFired(this);
        info.UpdateScore(current_state_->Get_Score());
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, current_state_->Get_Score());
    }
}

void KoopaTroopa::Set_Pos(Vector2 pos)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    position_ = pos;
}

void KoopaTroopa::Notify_Be_Kicked(int direction, PlayerInformation &info)
{
    // direction: 1 for right, -1 for left
    if (current_state_ && Can_Be_Kicked())
        current_state_->OnKicked(this, direction , info);
}

bool KoopaTroopa::Can_Be_Kicked() const
{
    return (dynamic_cast<KoopaShellIdleState *>(current_state_) != nullptr);
}

void KoopaTroopa::Notify_On_Ground()
{
    velocity_.y = -gravity_ * GetFrameTime(); // Reset vertical velocity
    is_ground = true;
}

bool KoopaTroopa::Kill_Other_Enemies() const
{
    return (dynamic_cast<KoopaShellMovingState *>(current_state_) != nullptr);
}