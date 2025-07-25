#include "Enemy/Enemy.h"

Enemy::Enemy(Vector2 startPos, Vector2 velocity, float gravity)
    : position_(startPos),
      velocity_(velocity),        // Khởi tạo với vận tốc truyền vào
      gravity_(gravity),         // Khởi tạo với trọng lực truyền vào
      frame_(0),                 // Khung hình hoạt hình ban đầu
      isGround_(false)           // Ban đầu không chạm đất
{};

Rectangle Enemy::Get_Draw_Rec() const
{
    // Trả về hình chữ nhật để vẽ sprite
    return {position_.x, position_.y , rec_.width * scale_screen, rec_.height * scale_screen};
}

Vector2 Enemy::Get_Pos() const
{
    return position_;
}

void Enemy::Notify_Fall(float deltaTime)
{
    // Mediator thông báo enemy đang rơi
    isGround_ = false;
    velocity_.y += gravity_ ; // Áp dụng trọng lực (giả sử dt = 1/60s)
}

void Enemy::Notify_On_Ground()
{
    // Mediator thông báo enemy chạm đất
    isGround_ = true;
    velocity_.y = 0.0f; // Dừng vận tốc theo y khi chạm đất
    rec_.y = position_.y; // Đồng bộ hóa vị trí của rec_ với position_
}

void Enemy::Notify_Change_Direct()
{
    // Mediator thông báo cần đổi hướng di chuyển
    velocity_.x = -velocity_.x; // Đảo ngược vận tốc theo x
}