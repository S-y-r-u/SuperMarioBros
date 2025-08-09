#include "Player.h"
#include "Enemy/PiranhaPlant.h"
#include "Sprite.h"
#include <cmath>

// Constructor: khởi tạo PiranhaPlant với vị trí và con trỏ tới Player
PiranhaPlant::PiranhaPlant(Vector2 pos, Player *player_ptr)
    : Enemy(pos, {0.0f, 0.0f}, 0.0f), // Không có velocity và gravity ban đầu
      player(player_ptr),
      state_(PiranhaPlant_State::underground),
      base_pos(pos),
      delta_time(0.0f),
      state_timer(0.0f),
      m_normal(Enemies_Sprite::Piranha_Plant_Green::plant_) // Chỉ load 1 sprite
{
    rec_ = m_normal[current_frame];
    position_ = base_pos;                       // Bắt đầu ở dưới ống
    is_ground = true;                           // Luôn "trên mặt đất" vì gắn với ống
    above_pos = {pos.x, pos.y - emerge_height}; // Vị trí khi nhô lên hoàn toàn
}

// Vẽ PiranhaPlant ra màn hình
void PiranhaPlant::Draw() const
{
    // Chỉ vẽ khi không ở trạng thái underground hoàn toàn
    if (state_ != PiranhaPlant_State::underground || state_timer < underground_duration)
    {
        Rectangle dest_rec = {
            position_.x,
            position_.y,
            rec_.width * scale_screen,
            rec_.height * scale_screen};

        DrawTexturePro(sprite_.sprite, rec_, dest_rec,
                       {rec_.width * scale_screen / 2.0f, rec_.height * scale_screen},
                       0.0f, WHITE);
    }
}

// Cập nhật trạng thái của PiranhaPlant mỗi frame
void PiranhaPlant::Update(float dt)
{
    UpdateStateMachine(dt);
    UpdatePosition(dt);
    Be_Fired_Or_Hit();
    Animate_();

    // PiranhaPlant không bao giờ rời khỏi màn hình trừ khi bị tiêu diệt
    if (state_ == PiranhaPlant_State::be_fired_or_hit && position_.y - rec_.height >= Screen_h)
        is_active = 0;
}

// PiranhaPlant không thể bị dậm lên
bool PiranhaPlant::Can_Be_Stomped() const { return false; }

// PiranhaPlant có thể bị tấn công bằng fireball
bool PiranhaPlant::Can_Be_Fired_Or_Hit() const { return true; }

// PiranhaPlant không bị ảnh hưởng bởi trọng lực thông thường
void PiranhaPlant::Notify_Fall(float dt) { /* Không làm gì */ }
void PiranhaPlant::Notify_On_Ground() { /* Không làm gì */ }
void PiranhaPlant::Notify_Be_Stomped(PlayerInformation& info) { /* Không thể bị stomp */ }

// Thông báo bị tấn công
void PiranhaPlant::Notify_Be_Fired_Or_Hit(PlayerInformation& info)
{
    if (state_ != PiranhaPlant_State::be_fired_or_hit)
    {
        info.UpdateScore(Score_PiranhaPlant); 
        Score_Manager &score_manager = Score_Manager::GetInstance();
        Rectangle dest_rec = Get_Draw_Rec();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, Score_PiranhaPlant);
        state_ = PiranhaPlant_State::be_fired_or_hit;
        delta_time = 0.0f;
        is_dead = 1;
    }
}

// Cập nhật vị trí (chỉ khi không bị tấn công)
void PiranhaPlant::Set_Pos(Vector2 pos)
{
    if (state_ != PiranhaPlant_State::be_fired_or_hit)
    {
        base_pos = pos;
        above_pos = {pos.x, pos.y - emerge_height};
    }
}

// Cập nhật state machine của PiranhaPlant
void PiranhaPlant::UpdateStateMachine(float dt)
{
    if (state_ == PiranhaPlant_State::be_fired_or_hit)
        return;

    state_timer += dt;

    switch (state_)
    {
    case PiranhaPlant_State::underground:
        if (state_timer >= underground_duration && IsPlayerNearby())
        {
            state_ = PiranhaPlant_State::emerging;
            state_timer = 0.0f;
        }
        break;

    case PiranhaPlant_State::emerging:
        // Khi nhô lên hoàn toàn, chuyển sang retreating sau thời gian above_duration
        if (position_.y <= above_pos.y)
        {
            position_.y = above_pos.y;
            if (state_timer >= above_duration)
            {
                state_ = PiranhaPlant_State::retreating;
                state_timer = 0.0f;
            }
        }
        break;

    case PiranhaPlant_State::retreating:
        if (position_.y >= base_pos.y)
        {
            position_.y = base_pos.y;
            state_ = PiranhaPlant_State::underground;
            state_timer = 0.0f;
        }
        break;
    }
}

// Cập nhật vị trí dựa trên trạng thái
void PiranhaPlant::UpdatePosition(float dt)
{
    if (state_ == PiranhaPlant_State::be_fired_or_hit)
        return;

    float target_y = GetCurrentTargetY();

    if (state_ == PiranhaPlant_State::emerging)
    {
        position_.y -= emerge_speed * dt;
        if (position_.y < target_y)
            position_.y = target_y;
    }
    else if (state_ == PiranhaPlant_State::retreating)
    {
        position_.y += emerge_speed * dt;
        if (position_.y > target_y)
            position_.y = target_y;
    }
}

// Cập nhật hoạt ảnh
void PiranhaPlant::Animate_()
{
    if (state_ == PiranhaPlant_State::be_fired_or_hit)
        return;

    frame_timer += GetFrameTime();

    // Dùng m_normal cho mọi trạng thái
    if (frame_timer >= 0.25f)
    {
        current_frame = (current_frame + 1) % m_normal.size();
        frame_timer = 0.0f;
    }
    rec_ = m_normal[current_frame];
}

// Xử lý khi bị tấn công
void PiranhaPlant::Be_Fired_Or_Hit()
{
    if (state_ == PiranhaPlant_State::be_fired_or_hit)
    {
        delta_time += 0.14f;
        // Quỹ đạo parabol bay lên rồi rơi xuống
        float deltaY = -Push_Height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
        position_.y = position_.y + deltaY;
    }
}

// Kiểm tra player có gần không
bool PiranhaPlant::IsPlayerNearby() const
{
    if (!player) return false;
    Vector2 player_pos = player->getPosition();
    float distance = std::abs(player_pos.x - position_.x);

    return distance < safe_distance;
}

// Lấy tọa độ Y mục tiêu dựa trên trạng thái
float PiranhaPlant::GetCurrentTargetY() const
{
    switch (state_)
    {
    case PiranhaPlant_State::underground:
        return base_pos.y;
    case PiranhaPlant_State::retreating:
        return base_pos.y;
    case PiranhaPlant_State::emerging:
        return above_pos.y;
    default:
        return position_.y;
    }
}