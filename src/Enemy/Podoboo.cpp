#include "Enemy/Podoboo.h"
#include <raylib.h>

Podoboo::Podoboo(Vector2 pos, float speed)
    : Enemy(pos, {0, speed}, 0.0f), previous_frame_pos_(pos), base_y_(pos.y), going_up_(true) {
        animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Podoboo::normal_, 1 / 4.0f);
    }

void Podoboo::Update(float dt) {
    previous_frame_pos_ = position_;
    if (going_up_) {
        position_.y -= velocity_.y * dt;
        if (position_.y <= base_y_ - jump_height_) {
            position_.y = base_y_ - jump_height_;
            going_up_ = false;
        }
    } else {
        position_.y += velocity_.y * dt;
        if (position_.y >= base_y_) {
            position_.y = base_y_;
            going_up_ = true;
        }
    }
}

void Podoboo::Draw() const {
    bool flip = !going_up_;
    Rectangle rec__ = {animation_.Get_Current_Rec().x, animation_.Get_Current_Rec().y,  animation_.Get_Current_Rec().width,flip ? -1.0f * animation_.Get_Current_Rec().height : animation_.Get_Current_Rec().height};
    float draw_width = animation_.Get_Current_Rec().width * scale_screen;
    float draw_height = animation_.Get_Current_Rec().height * scale_screen;
    Rectangle dest_rec = {position_.x, position_.y, draw_width, draw_height};
    Vector2 origin = {draw_width / 2.0f, draw_height};
    DrawTexturePro(animation_.Get_Sprite().sprite, rec__, dest_rec,
                   {origin.x, origin.y}, // Điểm neo ở giữa
                   0.0f, WHITE);
}

Vector2 Podoboo::Get_Previous_Pos() const {
    return previous_frame_pos_;
}

void Podoboo::Notify_Be_Fired_Or_Hit() {}

void Podoboo::Notify_Fall(float dt) {}
void Podoboo::Notify_On_Ground() {}

json Podoboo::to_json() const {
    return {
        {"x", position_.x},
        {"y", position_.y},
        {"vy", velocity_.y},
        {"base_y", base_y_},
        {"going_up", going_up_},
        {"is_active", is_active},
        {"is_dead", is_dead},
        {"is_ground", is_ground},
        {"first_appear", first_appear},
        {"score", score}
    };
}

void Podoboo::from_json(const json& j) {
    position_.x = j["x"];
    position_.y = j["y"];
    velocity_.y = j["vy"];
    base_y_ = j["base_y"];
    going_up_ = j["going_up"];
    is_active = j["is_active"];
    is_dead = j["is_dead"];
    is_ground = j["is_ground"];
    first_appear = j["first_appear"];
    score = j["score"];
}
