#include "Enemy/BomberBill.h"

BomberBill::BomberBill(Vector2 startPos, float maxDistance)
    : Enemy(startPos, {300.0f, 0}, 300.0f), // Không có trọng lực ban đầu
      max_distance(maxDistance),
      initial_x(startPos.x),
      state_(BomberBill_State::Flying),
      death_timer(0.0f)
{
    // Khởi tạo vector chứa 6 frame animation
    score = 100;
    animation_ = Animation(&BomberBill_Sprite::bomber_bill_, BomberBill_Sprite::bomber_bill_normal, 0.1);
    previous_frame_pos = startPos;
}

BomberBill::~BomberBill() {}

void BomberBill::Update(float dt)
{
    if (!is_active)
        return;

    // Lưu vị trí trước đó
    previous_frame_pos = position_;

    switch (state_)
    {
    case BomberBill_State::Flying:
        // Cập nhật animation bình thường
        Update_Animation(dt);

        // Kiểm tra nếu đã bay quá khoảng cách cho phép
        if (velocity_.x > 0 && (position_.x - initial_x) >= max_distance)
        {
            velocity_.x *= -1;
        }
        else if (velocity_.x < 0 && (position_.x - initial_x) <= -max_distance)
        {
            velocity_.x *= -1;
        }
        // Cập nhật vị trí - chỉ di chuyển theo x
        position_.x += velocity_.x * dt;
        break;

    case BomberBill_State::Dying:
        // Rơi xuống với trọng lực
        velocity_.y += gravity_ * dt;
        position_.x += velocity_.x * dt;
        position_.y += velocity_.y * dt;

        // Đếm thời gian chết
        death_timer += dt;
        if (death_timer >= death_duration)
        {
            state_ = BomberBill_State::Dead;
            is_active = false; // Biến mất
        }
        break;

    case BomberBill_State::Dead:
        // Không làm gì - đã biến mất
        break;
    }
}

void BomberBill::Update_Animation(float dt)
{
    if (state_ != BomberBill_State::Flying)
        return;

    animation_.Update(dt);
}

void BomberBill::Start_Death_Animation()
{
    is_dead = true;
    state_ = BomberBill_State::Dying;
    ;
    velocity_.x *= 0.5f;   // Giảm tốc độ ngang khi chết
    velocity_.y = -100.0f; // Bật lên một chút trước khi rơi
    death_timer = 0.0f;

    // Có thể thay đổi sprite thành sprite chết nếu có
    // rec_ = BomberBill_Sprite::death_sprite; // Nếu có sprite riêng cho chết
}

void BomberBill::Draw() const
{
    if (!is_active)
        return;

    Rectangle destRec = Get_Draw_Rec();
    Rectangle sourceRec = animation_.Get_Current_Rec(); // Sử dụng frame hiện tại

    // Thay đổi màu khi đang chết
    Color tint = (state_ == BomberBill_State::Dying) ? RED : WHITE;

    // Vẽ Bomber Bill với hướng phù hợp
    if (velocity_.x > 0) // Đang bay sang phải
    {
        sourceRec.width = -sourceRec.width; // Lật ngang
        // Bay sang phải - vẽ bình thường
        DrawTexturePro(animation_.Get_Sprite().sprite, sourceRec, destRec, {0, 0}, 0.0f, tint);
    }
    else
    {
        // Bay sang trái - lật ngang sprite
        DrawTexturePro(animation_.Get_Sprite().sprite, sourceRec, destRec, {0, 0}, 0.0f, tint);
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
    return (state_ == BomberBill_State::Flying); // Chỉ có thể giẫm khi đang bay
}

bool BomberBill::Can_Be_Fired_Or_Hit() const
{
    return false; // Chỉ có thể bắn khi đang bay
}

bool BomberBill::Need_Check_Map() const
{
    return false; // Chỉ kiểm tra ground khi đang rơi
}

void BomberBill::Notify_On_Ground()
{
    // Khi chạm đất trong lúc chết, biến mất luôn
    if (state_ == BomberBill_State::Dying)
    {
        state_ = BomberBill_State::Dead;
        is_active = false;
    }
}

void BomberBill::Notify_Be_Stomped()
{
    if (state_ == BomberBill_State::Flying)
    {
        Start_Death_Animation();
    }
}

json BomberBill::to_json() const
{
    json j;

    // Thuộc tính của Enemy
    j["position"] = {position_.x, position_.y};
    j["velocity"] = {velocity_.x, velocity_.y};
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;

    // Thuộc tính của BomberBill
    j["initial_x"] = initial_x;
    j["previous_frame_pos"] = {previous_frame_pos.x, previous_frame_pos.y};
    j["state"] = static_cast<int>(state_);
    j["death_timer"] = death_timer;

    return j;
}

void BomberBill::from_json(const json &j)
{
    // Thuộc tính của Enemy
    position_.x = j.at("position")[0];
    position_.y = j.at("position")[1];
    velocity_.x = j.at("velocity")[0];
    velocity_.y = j.at("velocity")[1];
    gravity_ = j.at("gravity");
    is_ground = j.at("is_ground");
    is_active = j.at("is_active");
    is_dead = j.at("is_dead");
    first_appear = j.at("first_appear");

    // Thuộc tính của BomberBill
    initial_x = j.at("initial_x");
    previous_frame_pos.x = j.at("previous_frame_pos")[0];
    previous_frame_pos.y = j.at("previous_frame_pos")[1];
    state_ = static_cast<BomberBill_State>(j.at("state").get<int>());
    death_timer = j.at("death_timer");
}