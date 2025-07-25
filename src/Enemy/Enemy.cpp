#include "Enemy/Enemy.h"

Enemy::Enemy(Vector2 startPos, Vector2 velocity, float gravity)
    : sprite_(Enemies_Sprite::enemies_),
      position_(startPos),
      velocity_(velocity), // Khởi tạo với vận tốc truyền vào
      gravity_(gravity),   // Khởi tạo với trọng lực truyền vào
      frame_timer(0),      // Khung hình hoạt hình ban đầu
      current_frame(0),
      be_fired(0), be_stomped(0),
      is_ground(false), // Ban đầu không chạm đất
      is_active(1),
      is_dead(0) {};

Enemy::~Enemy() {}

Rectangle Enemy::Get_Draw_Rec() const
{
    // Trả về hình chữ nhật để vẽ sprite
    return {position_.x - rec_.width * scale_screen / 2.0f, position_.y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen};
}

Vector2 Enemy::Get_Pos() const
{
    return position_;
}

bool Enemy::Get_Is_Active() { return is_active; }

bool Enemy::Get_Is_Dead() { return is_dead; }

void Enemy::Notify_Fall(float dt)
{
    // Mediator thông báo enemy đang rơi
    is_ground = false;
    velocity_.y += gravity_ * dt; // Áp dụng trọng lực (giả sử dt = 1/60s)
}

void Enemy::Notify_On_Ground()
{
    // Mediator thông báo enemy chạm đất
    is_ground = true;
    velocity_.y = 0.0f;   // Dừng vận tốc theo y khi chạm đất
    rec_.y = position_.y; // Đồng bộ hóa vị trí của rec_ với position_
}

void Enemy::Notify_Change_Direct()
{
    // Mediator thông báo cần đổi hướng di chuyển
    velocity_.x = -velocity_.x; // Đảo ngược vận tốc theo x
}
