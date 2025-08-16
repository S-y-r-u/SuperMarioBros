#include "Enemy/CheepCheep.h"
#include <raylib.h>

CheepCheep::CheepCheep(Vector2 pos,Player* player, float vx, float vy, float gravity)
    : Enemy(pos, {vx, vy}, gravity), previous_frame_pos_(pos), base_y_(pos.y), player(player) {
    animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Cheep_Cheep::normal_::normal_, 1 / 4.0f);
    score = 200 ;
}

void CheepCheep::Update(float dt) {
    previous_frame_pos_ = position_;
    // Bay lên
    if (state_ == CheepCheepState::Normal) {
        velocity_.y += gravity_ * dt;
        position_ += velocity_ * dt;
    }
    if (position_.y >= base_y_) {
        position_.y = base_y_;
        // Xác định hướng bay tiếp theo
        if (position_.x < player->getPosition().x) velocity_.x = fabs(velocity_.x);
        else velocity_.x = -fabs(velocity_.x);
        velocity_.y = -fabs(velocity_.y); // Nhảy lên lại
    }
    if (state_ == CheepCheepState::Dying){
        position_.y += dying_speed * dt;
        dying_timer_ += dt;
        if (dying_timer_ >= dying_animation_timer) {
            is_active = false;
        }
    }
    animation_.Update(dt);
}

void CheepCheep::Draw() const {
    bool flip = velocity_.x > 0;
    Rectangle rec__ = {animation_.Get_Current_Rec().x, animation_.Get_Current_Rec().y, flip ? -animation_.Get_Current_Rec().width : animation_.Get_Current_Rec().width, animation_.Get_Current_Rec().height};
    float draw_width = fabs(animation_.Get_Current_Rec().width) * scale_screen;
    float draw_height = animation_.Get_Current_Rec().height * scale_screen;
    Rectangle dest_rec = {position_.x, position_.y, draw_width, draw_height};
    Vector2 origin = {draw_width / 2.0f, draw_height};
    DrawTexturePro(animation_.Get_Sprite().sprite, rec__, dest_rec, {origin.x, origin.y}, 0.0f, WHITE);
}

Vector2 CheepCheep::Get_Previous_Pos() const {
    return previous_frame_pos_;
}

void CheepCheep::Notify_Be_Fired_Or_Hit() {
    state_ = CheepCheepState::Dying;
    animation_.Set_Frames(Enemies_Sprite::Cheep_Cheep::dying_::dying_);
    is_dead = true ;
}
void CheepCheep::Notify_Be_Stomped() {
    state_ = CheepCheepState::Dying;
    animation_.Set_Frames(Enemies_Sprite::Cheep_Cheep::dying_::dying_);
    is_dead = true;
}

json CheepCheep::to_json() const {
    return {
        {"x", position_.x},
        {"y", position_.y},
        {"vx", velocity_.x},
        {"vy", velocity_.y},
        {"base_y", base_y_},
        {"is_active", is_active},
        {"is_dead", is_dead},
        {"is_ground", is_ground},
        {"first_appear", first_appear},
        {"score", score},
        {"dying_timer", dying_timer_}
    };
}

void CheepCheep::from_json(const json& j) {
    position_.x = j["x"];
    position_.y = j["y"];
    velocity_.x = j["vx"];
    velocity_.y = j["vy"];
    base_y_ = j["base_y"];
    is_active = j["is_active"];
    is_dead = j["is_dead"];
    is_ground = j["is_ground"];
    first_appear = j["first_appear"];
    score = j["score"];
    dying_timer_ = j["dying_timer"];
}
