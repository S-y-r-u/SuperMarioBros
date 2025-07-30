#include "Enemy/Spiny.h"

// Constructor khởi tạo Spiny ở trạng thái "egg"
Spiny::Spiny(Vector2 pos, Vector2 velo, float gravity)
    : Enemy(pos, velo, gravity),
      state_(Spiny_State::egg),
      m_egg(Enemies_Sprite::Spiny::Egg::egg_),
      m_normal(Enemies_Sprite::Spiny::Normal::normal_),
      delta_time(0.0f),
      before_pos(pos),
      is_jump(0)
{
    rec_ = m_egg[current_frame]; // Thiết lập khung hình ban đầu là egg
}

// Cập nhật logic của Spiny mỗi frame
void Spiny::Update(float dt)
{
    Fall_();           // Xử lý rơi tự do
    Move_(dt);         // Xử lý di chuyển ngang
    Jump_(dt);         // Xử lý nhảy
    Animate_();        // Xử lý hoạt ảnh
    Be_Fired_Or_Hit(); // Xử lý trạng thái bị bắn hoặc đánh
    if (position_.y - rec_.height >= Screen_h)
        is_active = 0; // Vô hiệu hóa Spiny nếu rơi khỏi màn hình
}

// Vẽ Spiny lên màn hình
void Spiny::Draw() const
{
    Rectangle src_rec = rec_;
    // Lật hình nếu di chuyển trái/phải
    if (velocity_.x < 0)
        src_rec.width = std::abs(src_rec.width);
    else
        src_rec.width = -std::abs(src_rec.width);

    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src_rec.width) * scale_screen,
        src_rec.height * scale_screen};

    DrawTexturePro(sprite_.sprite, src_rec, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

Vector2 Spiny::Get_Previous_Pos() const { return previous_frame_pos; }

// Được gọi khi Spiny bắt đầu rơi
void Spiny::Notify_Fall(float dt)
{
    if (is_ground && state_ != Spiny_State::be_fired_or_hit)
    {
        is_ground = 0;
        before_pos = position_;
    }
}

// Được gọi khi Spiny chạm đất
void Spiny::Notify_On_Ground()
{
    if (state_ == Spiny_State::be_fired_or_hit)
        return;

    is_jump = 0;
    is_ground = 1;
    delta_time = 0.0f;

    // Nếu còn là trứng thì chuyển sang trạng thái bình thường
    if (state_ == Spiny_State::egg)
    {
        state_ = Spiny_State::normal;
        frame_timer = current_frame = 0;
        rec_ = m_normal[current_frame];
    }
}

// Được gọi khi Spiny nhảy lên (ví dụ sau khi bị Lakitu ném ra)
void Spiny::Notify_Jump()
{
    if (state_ == Spiny_State::normal)
    {
        is_jump = 1;
        is_ground = 0;
        delta_time = 0.0f;
        before_pos = position_;
    }
}

// Spiny không thể bị giẫm
bool Spiny::Can_Be_Stomped() const { return false; }

// Spiny có thể bị bắn hoặc đánh
bool Spiny::Can_Be_Fired_Or_Hit() const { return true; }

// Được gọi khi Spiny bị bắn hoặc đánh
void Spiny::Notify_Be_Fired_Or_Hit()
{
    if (state_ == Spiny_State::normal)
    {
        state_ = Spiny_State::be_fired_or_hit;
        rec_ = Enemies_Sprite::Spiny::be_fired_or_hit;
        before_pos = position_;
        delta_time = 0.0f;
        is_dead = 1;
    }
}

// Đặt lại vị trí cho Spiny (nếu không đang bị tiêu diệt)
void Spiny::Set_Pos(Vector2 pos)
{
    if (state_ != Spiny_State::be_fired_or_hit)
        position_ = pos;
}

// Xử lý hoạt ảnh theo trạng thái hiện tại
void Spiny::Animate_()
{
    if (state_ == Spiny_State::be_fired_or_hit)
        return;

    frame_timer++;

    // Đổi frame hoạt ảnh nếu là trứng
    if (frame_timer >= 10 && state_ == Spiny_State::egg)
    {
        frame_timer = 0;
        current_frame = (current_frame + 1) % m_egg.size();
        rec_ = m_egg[current_frame];
    }
    // Đổi frame hoạt ảnh nếu là Spiny thường
    else if (frame_timer >= 15 && state_ == Spiny_State::normal)
    {
        frame_timer = 0;
        current_frame = (current_frame + 1) % m_normal.size();
        rec_ = m_normal[current_frame];
    }
}

// Logic rơi tự do khi Spiny ở trạng thái egg hoặc normal
void Spiny::Fall_()
{
    if (is_ground || is_jump || state_ == Spiny_State::be_fired_or_hit)
        return;

    previous_frame_pos = position_;
    delta_time += 0.18f;

    float deltaY;
    if (state_ == Spiny_State::egg)
        deltaY = -Ini_Velo * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
    else
        deltaY = 0.5f * delta_time * delta_time * Physics::gravity_;

    position_.y = before_pos.y + deltaY;
}

// Di chuyển ngang khi đang ở trên mặt đất và không nhảy
void Spiny::Move_(float dt)
{
    if (!is_ground || is_jump || state_ == Spiny_State::be_fired_or_hit)
        return;

    previous_frame_pos = position_;
    position_ += velocity_ * dt;

    // Đổi hướng khi chạm mép bản đồ
    if (position_.x <= 0.0f || position_.x + rec_.width >= 214 * 48.0f)
        velocity_.x *= -1;
}

// Xử lý khi bị bắn hoặc đánh – rơi lên rồi rớt xuống
void Spiny::Be_Fired_Or_Hit()
{
    if (state_ == Spiny_State::be_fired_or_hit)
    {
        delta_time += 0.14f;
        float deltaY = -Push_Height * delta_time + 0.5 * delta_time * delta_time * Physics::gravity_;
        position_.y = before_pos.y + deltaY;
    }
}

// Logic nhảy – áp dụng cho trạng thái `normal`
void Spiny::Jump_(float dt)
{
    if (!is_jump)
        return;

    previous_frame_pos = position_;
    delta_time += 0.18f;

    float deltaY = -Ini_Velo * delta_time + 0.5 * delta_time * delta_time * Physics::gravity_;
    position_.y = before_pos.y + deltaY;
    position_ += velocity_ * dt;

    // Đổi hướng nếu chạm mép màn hình
    if (position_.x <= 0.0f || position_.x + rec_.width >= 214 * 48.0f)
        velocity_.x *= -1;
}
