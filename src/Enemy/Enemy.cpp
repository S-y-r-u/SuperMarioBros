#include "Enemy/Enemy.h"

Enemy::Enemy(Vector2 startPos, Vector2 velocity, float gravity)
    : animation_(nullptr), // Khởi tạo animation với nullptr
      position_(startPos),
      velocity_(velocity), // Khởi tạo với vận tốc truyền vào
      gravity_(gravity),   // Khởi tạo với trọng lực truyền vào
      is_ground(false),    // Ban đầu không chạm đất
      is_active(1),
      is_dead(0),
      score(0) {};

Enemy::~Enemy() {}

Rectangle Enemy::Get_Draw_Rec() const
{
    // Trả về hình chữ nhật để vẽ sprite
    return {position_.x - animation_.Get_Current_Rec().width * scale_screen / 2.0f, position_.y - animation_.Get_Current_Rec().height * scale_screen, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
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

int Enemy::Get_Score() { return score; }

void Enemy::Notify_Change_Direct()
{
    // Mediator thông báo cần đổi hướng di chuyển
    velocity_.x = -velocity_.x; // Đảo ngược vận tốc theo x
}

bool Enemy::Can_Be_Kicked() const { return false; }

bool Enemy::Can_Jump() const { return false; }

bool Enemy::Need_Check_Map() const { return true; }

void Enemy::Collision_With_Other_Enemy(Enemy *other)
{
    if (this->Kill_Enemy())
        other->Notify_Be_Fired_Or_Hit();
    else
    {
        if (velocity_.x * other->Get_Velocity().x < 0)
            Notify_Change_Direct();
        else if (position_.x < other->Get_Pos().x && velocity_.x > 0)
            Notify_Change_Direct();
        else if (position_.x > other->Get_Pos().x && velocity_.x < 0)
            Notify_Change_Direct();
    }
}

void Enemy::Set_Velocity(Vector2 velocity)
{
    if (!is_active || is_dead)
        return;
    velocity_ = velocity;
}

bool Enemy::Kill_Enemy() { return false; }
