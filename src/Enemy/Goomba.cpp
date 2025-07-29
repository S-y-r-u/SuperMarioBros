#include "Enemy/Goomba.h"

// Constructor: khởi tạo Goomba với vị trí, vận tốc, trọng lực và trạng thái ban đầu
Goomba::Goomba(Vector2 pos, Vector2 velo, float gravity)
    : Enemy(pos, velo, gravity),
      before_pos(position_), // Vị trí trước khi rơi
      delta_time(0.0f),
      state_(Goomba_State::normal), // Trạng thái mặc định là "bình thường"
      m_normal(Enemies_Sprite::Goomba_Brown::Normal::normal_)
{
    rec_ = m_normal[current_frame]; // Frame hiện tại để vẽ
}

// Vẽ Goomba ra màn hình
void Goomba::Draw() const
{
    Rectangle dest_rec = {position_.x, position_.y, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(sprite_.sprite, rec_, dest_rec,
                   {rec_.width * scale_screen / 2.0f, rec_.height * scale_screen}, // Điểm neo ở giữa
                   0.0f, WHITE);
}

// Cập nhật trạng thái của Goomba mỗi frame
void Goomba::Update(float dt)
{
    Fall_();           // Nếu đang rơi, cập nhật vị trí rơi
    Move_(dt);         // Nếu đang di chuyển trên mặt đất, cập nhật vị trí
    Be_Stomped();      // Kiểm tra và xử lý nếu bị dậm lên
    Be_Fired_Or_Hit(); // Kiểm tra và xử lý nếu bị bắn hoặc tấn công
    Animate_();        // Cập nhật hoạt ảnh
    if (position_.y - rec_.height >= Screen_h)
        is_active = 0;
}

// Cho phép Goomba bị dậm lên
bool Goomba::Can_Be_Stomped() const { return true; }

// Cho phép Goomba bị bắn hoặc tấn công
bool Goomba::Can_Be_Fired_Or_Hit() const { return true; }

Vector2 Goomba::Get_Previous_Pos() const { return previous_frame_pos; }

// Thông báo rằng Goomba bắt đầu rơi
void Goomba::Notify_Fall(float dt)
{
    // Nếu đã tiếp đất hoặc không phải trạng thái bình thường thì bỏ qua
    if (is_ground && state_ == Goomba_State::normal)
    {
        is_ground = 0;
        before_pos = position_; // Ghi lại vị trí bắt đầu rơi
    }
}

// Thông báo rằng Goomba chạm đất
void Goomba::Notify_On_Ground()
{
    if (state_ == Goomba_State::normal)
    {
        is_ground = 1;
        delta_time = 0.0f; // Reset thời gian rơi
    }
}

// Thông báo rằng Goomba bị dậm lên
void Goomba::Notify_Be_Stomped()
{
    if (state_ == Goomba_State::normal)
    {
        state_ = Goomba_State::be_stomped;
        rec_ = Enemies_Sprite::Goomba_Brown::be_stomped; // Chuyển frame sang trạng thái bị dậm
        is_dead = 1;
    }
}

// Thông báo rằng Goomba bị tấn công bởi lửa hoặc vật thể
void Goomba::Notify_Be_Fired_Or_Hit()
{
    if (state_ == Goomba_State::normal)
    {
        state_ = Goomba_State::be_fired_or_hit;
        rec_ = Enemies_Sprite::Goomba_Brown::be_fired_or_hit;
        delta_time = 0.0f;
        before_pos = position_; // Ghi lại vị trí để tính quỹ đạo bay
        is_dead = 1;
    }
}

// Cập nhật vị trí thủ công (chỉ nếu ở trạng thái bình thường)
void Goomba::Set_Pos(Vector2 pos)
{
    if (state_ == Goomba_State::normal)
    {
        position_ = pos;
    }
}

// Xử lý rơi tự do khi ở trên không
void Goomba::Fall_()
{
    if (is_ground || state_ != Goomba_State::normal)
        return;
    delta_time += 0.18f;
    float deltaY = 0.5 * delta_time * delta_time * Physics::gravity_;
    position_.y = before_pos.y + deltaY;
}

// Xử lý di chuyển trên mặt đất (trái/phải)
void Goomba::Move_(float dt)
{
    if (!is_ground || state_ != Goomba_State::normal)
        return;
    position_ += velocity_ * dt;

    // Đảo chiều nếu va chạm biên trái/phải
    if (position_.x <= 0.0f || position_.x + rec_.width >= 214 * 48.0f)
        velocity_ *= -1;
}

// Xử lý hoạt ảnh đi bộ của Goomba
void Goomba::Animate_()
{
    if (state_ == Goomba_State::normal)
    {
        frame_timer++;
        if (frame_timer >= 8) // Mỗi 8 frame thì đổi hình
        {
            current_frame = (current_frame + 1) % m_normal.size();
            frame_timer = 0;
        }
        rec_ = m_normal[current_frame];
    }
}

// Xử lý Goomba sau khi bị dậm
void Goomba::Be_Stomped()
{
    if (state_ == Goomba_State::be_stomped)
    {
        stomped_timer++;
        if (stomped_timer >= Stomped_Duration)
        {
            is_active = 0; // Xoá khỏi màn chơi
        }
    }
}

// Xử lý Goomba sau khi bị fireball hoặc đập vào
void Goomba::Be_Fired_Or_Hit()
{
    if (state_ == Goomba_State::be_fired_or_hit)
    {
        delta_time += 0.14f;
        // Tính quỹ đạo parabol bay lên rồi rơi xuống
        float deltaY = -Push_Height * delta_time + 0.5 * delta_time * delta_time * Physics::gravity_;
        position_.y = before_pos.y + deltaY;
    }
}
