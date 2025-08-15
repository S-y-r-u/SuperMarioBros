#include "Enemy/LaserFire.h"
#include <raylib.h>
#include <cmath>

LaserFire::LaserFire(Vector2 pos, Vector2 target, float speed)
    : Enemy(pos, {0,0}, 0.0f), previous_frame_pos_(pos) {
    // Tính vận tốc theo hướng từ pos đến target
    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    float len = std::sqrt(dx*dx + dy*dy);
    if (len > 0.01f) {
        velocity_.x = speed * dx / len;
        velocity_.y = speed * dy / len;
    } else {
        velocity_ = {speed, 0};
    }
    animation_ = Animation(&Bowser_Sprite::bowser_, Bowser_Sprite::fire_laser_::fire_laser_, 1 / 4.0f);
    score = 100 ;
}

void LaserFire::Update(float dt) {
    previous_frame_pos_ = position_;
    position_.x += velocity_.x * dt;
    position_.y += velocity_.y * dt;
    life_time_ -= dt;
    if (life_time_ <= 0) is_active = false;
}

void LaserFire::Draw() const {
    bool flip = velocity_.x >= 0;
    Rectangle rec__ = {animation_.Get_Current_Rec().x, animation_.Get_Current_Rec().y, flip ? -1.0f * animation_.Get_Current_Rec().width : animation_.Get_Current_Rec().width, animation_.Get_Current_Rec().height};
    float draw_width = animation_.Get_Current_Rec().width * scale_screen;
    float draw_height = animation_.Get_Current_Rec().height * scale_screen;
    Rectangle dest_rec = {position_.x, position_.y, draw_width, draw_height};
    Vector2 origin = {draw_width / 2.0f, draw_height};
    DrawTexturePro(animation_.Get_Sprite().sprite, rec__, dest_rec,
                   {origin.x, origin.y}, // Điểm neo ở giữa
                   0.0f, WHITE);
}

Vector2 LaserFire::Get_Previous_Pos() const {
    return previous_frame_pos_;
}

json LaserFire::to_json() const {
    json j;

    // Thuộc tính kế thừa từ Enemy
    j["position"] = { position_.x, position_.y };
    j["velocity"] = { velocity_.x, velocity_.y };
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;
    j["_life_time"] = life_time_;

    return j;
}

void LaserFire::from_json(const json& j) {
    // Thuộc tính kế thừa từ Enemy
    position_.x = j.at("position")[0];
    position_.y = j.at("position")[1];
    velocity_.x = j.at("velocity")[0];
    velocity_.y = j.at("velocity")[1];
    gravity_ = j.at("gravity");
    is_ground = j.at("is_ground");
    is_active = j.at("is_active");
    is_dead = j.at("is_dead");
    first_appear = j.at("first_appear");
    life_time_ = j.at("_life_time");
}
