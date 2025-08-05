#include "Enemy/BomberBill.h"

BomberBill::BomberBill(Vector2 startPos, float maxDistance, float speed)
    : Enemy(startPos, {speed, 0}, 0.0f), // Không có trọng lực, bay ngang với tốc độ speed
      max_distance(maxDistance),
      initial_x(startPos.x),
      moving_right(true),
      run_speed(speed),
      asprite_(BomberBill_Sprite::bomber_bill_),
      animation_timer(0.0f),
      m_normal(BomberBill_Sprite::bomber_bill_normal),
      current_frame(0)
{
    // Khởi tạo vector chứa 6 frame animation
    
    // Thiết lập sprite rectangle ban đầu
    rec_ = m_normal[0]; // Frame đầu tiên
    previous_frame_pos = startPos;
}

BomberBill::~BomberBill() {}

void BomberBill::Update(float dt)
{
    if (!is_active || is_dead)
        return;

    // Lưu vị trí trước đó
    previous_frame_pos = position_;

    // Cập nhật animation
    Update_Animation(dt);

    // Kiểm tra nếu đã bay quá khoảng cách cho phép
    if (moving_right && (position_.x - initial_x) >= max_distance)
    {
        // Quay đầu - bay sang trái
        moving_right = false;
        velocity_.x = -run_speed;
    }
    // Kiểm tra nếu đã bay về vị trí ban đầu
    else if (!moving_right && (position_.x - initial_x) <= -max_distance)
    {
        // Quay đầu - bay sang phải
        moving_right = true;
        velocity_.x = run_speed;
    }

    // Cập nhật vị trí - chỉ di chuyển theo x, y giữ nguyên
    position_.x += velocity_.x * dt;
}

void BomberBill::Update_Animation(float dt)
{
    animation_timer += dt;
    
    if (animation_timer >= frame_duration)
    {
        // Chuyển sang frame tiếp theo
        current_frame = (current_frame + 1) % m_normal.size(); // Lặp qua 6 frame
        rec_ = m_normal[current_frame]; // Cập nhật rectangle hiện tại
        animation_timer = 0.0f; // Reset timer
    }
}

void BomberBill::Draw() const
{
    if (!is_active || is_dead)
        return;

    Rectangle destRec = Get_Draw_Rec();
    Rectangle sourceRec = rec_; // Sử dụng frame hiện tại
    
    // Vẽ Bomber Bill với hướng phù hợp
    if (moving_right)
    {
        // Bay sang phải - vẽ bình thường
        sourceRec.width = -sourceRec.width; // Lật ngang
        DrawTexturePro(asprite_.sprite, sourceRec, destRec, {0, 0}, 0.0f, WHITE);
    }
    else
    {
        // Bay sang trái - lật ngang sprite
        DrawTexturePro(asprite_.sprite, sourceRec, destRec, {0, 0}, 0.0f, WHITE);
    }
}

Vector2 BomberBill::Get_Previous_Pos() const
{
    return previous_frame_pos;
}

void BomberBill::Set_Pos(Vector2 pos)
{
    position_ = pos;
}

bool BomberBill::Can_Be_Stomped() const
{
    return false; // Bomber Bill bay nên không thể bị giẫm
}

bool BomberBill::Can_Be_Fired_Or_Hit() const
{
    return true; // Có thể bị bắn hoặc đánh
}

bool BomberBill::Need_Check_Ground_Block() const
{
    return false; // Không cần kiểm tra va chạm với đất vì bay trong không khí
}

void BomberBill::Notify_Fall(float dt)
{
    // Bomber Bill bay nên không bị rơi - không làm gì
}

void BomberBill::Notify_On_Ground()
{
    // Bomber Bill bay nên không chạm đất - không làm gì
}