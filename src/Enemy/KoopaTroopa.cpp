#include "Enemy\KoopaTroopa.h"
#include "Enemy\KoopaTroopaState.h"

KoopaTroopa::KoopaTroopa(Vector2 pos)
    : Enemy(pos, {-75.0f, 0}, 1000.0f),
      current_state_(nullptr),
      previous_state(nullptr),
      before_pos_(pos)
{
    animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Troopa_Green::Normal::normal_, 1 / 6.0f);
    SetState(new KoopaWalkingState());
}

// Constructor cho flying koopa
KoopaTroopa::KoopaTroopa(Vector2 pos, bool is_flying)
    : Enemy(pos, {-120.0f, 0}, 1000.0f),
      current_state_(nullptr),
      previous_state(nullptr),
      before_pos_(pos)
{
    if (is_flying)
    {
        SetState(new KoopaFlyingState());
    }
    else
    {
        SetState(new KoopaWalkingState());
    }
}

KoopaTroopa::~KoopaTroopa()
{
    delete previous_state;
    delete current_state_;
}

void KoopaTroopa::SetState(KoopaState *new_state)
{
    delete previous_state;
    previous_state = current_state_;
    current_state_ = new_state;
    if (current_state_)
        current_state_->Enter(this);
}

void KoopaTroopa::Notify_Fall(float dt)
{

    if (current_state_)
    {
        current_state_->Update(this, dt);
    }
}

void KoopaTroopa::Update(float dt)
{
    if (!is_active)
        return;
    // Apply velocity to position
    if (is_dead)
    {
        if (current_state_)
            current_state_->Update(this, dt);
    }
    before_pos_ = position_; // Lưu vị trí trước khi cập nhật
    position_ = Vector2Add(position_, Vector2Scale(velocity_, dt));
}

void KoopaTroopa::Draw() const
{
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

void KoopaTroopa::Notify_Be_Stomped(PlayerInformation &info)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    if (current_state_)
    {
        current_state_->OnStomped(this, info);
        info.UpdateScore(current_state_->Get_Score());
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, current_state_->Get_Score());
    }
}

void KoopaTroopa::Notify_Be_Fired_Or_Hit(PlayerInformation &info)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    if (current_state_)
    {
        current_state_->OnFired(this);
        info.UpdateScore(current_state_->Get_Score());
        Rectangle dest_rec = Get_Draw_Rec();
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, current_state_->Get_Score());
    }
}

void KoopaTroopa::Set_Pos(Vector2 pos)
{
    if (!Get_Is_Active() || Get_Is_Dead())
        return;
    position_ = pos;
}

void KoopaTroopa::Notify_Be_Kicked(int direction, PlayerInformation &info)
{
    // direction: 1 for right, -1 for left
    if (current_state_ && Can_Be_Kicked())
        current_state_->OnKicked(this, direction, info);
}

bool KoopaTroopa::Can_Be_Kicked() const
{
    return (dynamic_cast<KoopaShellIdleState *>(current_state_) != nullptr);
}

void KoopaTroopa::Notify_On_Ground()
{
    velocity_.y = -gravity_ * GetFrameTime(); // Reset vertical velocity
    is_ground = true;
}

bool KoopaTroopa::Kill_Other_Enemies() const
{
    return (dynamic_cast<KoopaShellMovingState *>(current_state_) != nullptr);
}

void KoopaTroopa::Collision_With_Other_Enemy(Vector2 velo, Vector2 pos)
{
    Notify_Change_Direct();
}
json KoopaTroopa::to_json() const {
    json j;

    // Enemy base
    j["position"] = { position_.x, position_.y };
    j["velocity"] = { velocity_.x, velocity_.y };
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;

    // KoopaTroopa riêng
    j["before_pos"] = { before_pos_.x, before_pos_.y };

    // Lưu state
    json state_json;
    if (auto s = dynamic_cast<KoopaWalkingState*>(current_state_)) {
        state_json["name"] = "walking";
    } else if (auto s = dynamic_cast<KoopaShellIdleState*>(current_state_)) {
        state_json["name"] = "shell_idle";
        state_json["timer"] = s->GetTimer(); // cần hàm getter
    } else if (auto s = dynamic_cast<KoopaShellMovingState*>(current_state_)) {
        state_json["name"] = "shell_moving";
    } else if (auto s = dynamic_cast<KoopaDyingState*>(current_state_)) {
        state_json["name"] = "dying";
    } else if (auto s = dynamic_cast<KoopaFlyingState*>(current_state_)) {
        state_json["name"] = "flying";
        state_json["flying_timer"] = s->GetFlyingTimer();
    }
    j["state"] = state_json;

    return j;
}

void KoopaTroopa::from_json(const json& j) {
    // Enemy base
    position_.x = j.at("position")[0];
    position_.y = j.at("position")[1];
    velocity_.x = j.at("velocity")[0];
    velocity_.y = j.at("velocity")[1];
    gravity_ = j.at("gravity");
    is_ground = j.at("is_ground");
    is_active = j.at("is_active");
    is_dead = j.at("is_dead");
    first_appear = j.at("first_appear");

    // KoopaTroopa riêng
    before_pos_.x = j.at("before_pos")[0];
    before_pos_.y = j.at("before_pos")[1];

    // State
    auto state_json = j.at("state");
    std::string name = state_json.at("name").get<std::string>();

    if (name == "walking") {
        SetState(new KoopaWalkingState());
    } else if (name == "shell_idle") {
        auto s = new KoopaShellIdleState();
        s->SetTimer(state_json.at("timer")); // cần hàm setter
        SetState(s);
    } else if (name == "shell_moving") {
        auto s = new KoopaShellMovingState();
        SetState(s);
    } else if (name == "dying") {
        SetState(new KoopaDyingState());
    } else if (name == "flying") {
        auto s = new KoopaFlyingState();
        s->SetFlyingTimer(state_json.at("flying_timer"));
        SetState(s);
    }
}


