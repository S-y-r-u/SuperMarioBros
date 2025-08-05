#include "Enemy/Enemy.h"

Enemy::Enemy(Vector2 startPos, Vector2 velocity, float gravity)
    : sprite_(Enemies_Sprite::enemies_),
      position_(startPos),
      velocity_(velocity), // Khởi tạo với vận tốc truyền vào
      gravity_(gravity),   // Khởi tạo với trọng lực truyền vào
      frame_timer(0.0f),   // Khung hình hoạt hình ban đầu
      current_frame(0),
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

Vector2 Enemy::Get_Velocity() const
{
    return velocity_;
}

bool Enemy::Get_Is_Active() { return is_active; }

bool Enemy::Get_Is_Dead() { return is_dead; }

void Enemy::Notify_Change_Direct()
{
    // Mediator thông báo cần đổi hướng di chuyển
    velocity_.x = -velocity_.x; // Đảo ngược vận tốc theo x
}

bool Enemy::Can_Be_Kicked() const { return false; }

bool Enemy::Can_Jump() const { return false; }

bool Enemy::Need_Check_Ground_Block() const { return true; }

bool Enemy::Kill_Other_Enemies() const { return false; }

void Enemy::Collision_With_Other_Enemy(Vector2 velo, Vector2 pos)
{
    if (velocity_.x * velo.x < 0)
        Notify_Change_Direct();
    else if(position_.x < pos.x && velocity_.x > 0) 
        Notify_Change_Direct();
    else if(position_.x > pos.x && velocity_.x < 0)
        Notify_Change_Direct();
}

bool Enemy::Need_Check_Collision_With_Other_Enemy() const
{
    return true; // Mặc định là cần kiểm tra va chạm với các enemy khác
}

void Enemy::Set_Velocity(Vector2 velocity)
{
    if (!is_active || is_dead)
        return;
    velocity_ = velocity; 
}