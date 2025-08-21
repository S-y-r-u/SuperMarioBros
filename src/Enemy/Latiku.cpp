#include "Enemy/Latiku.h"
#include "Constants.h"
#include <raymath.h>

// Constructor: khởi tạo Latiku với vị trí, trọng lực, con trỏ tới Player và danh sách kẻ địch
Latiku::Latiku(Vector2 pos, Player *&player, std::vector<Enemy *> *enemies, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map, Camera2D &camera)
    : Enemy(pos, {120.0f, 0}, 0.0f),
      player(player),
      state_(Latiku_State::fly),
      enemies(enemies),
      base_y(pos.y),
      camera(camera),
      pos_state(0),
      timer_(0.0f),
      pos_to_player(hover_radius),
      enemy_map(enemy_map)
{
    score = 1000;
    animation_ = Animation(&Enemies_Sprite::enemies_, Enemies_Sprite::Latiku::fly_);
}

// Hàm cập nhật trạng thái mỗi frame
void Latiku::Update(float dt)
{
    Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

    Rectangle screen_rect_world = {
        top_left.x,
        top_left.y,
        bottom_right.x - top_left.x,
        bottom_right.y - top_left.y};
    if (214 * Tile_Size - top_left.x <= dis_to_finish)
    {
        state_ = Latiku_State::disappear;
    }
    if (state_ == Latiku_State::be_fired_or_hit)
    {
        velocity_.y += Physics::gravity_ * dt;
        position_.y += velocity_.y * dt;
    }
    else if (state_ == Latiku_State::disappear)
    {
        Disappear_(dt);
    }
    else
    {
        Animate_(dt);
    }

    if (position_.y - animation_.Get_Current_Rec().height >= Screen_h)
        is_active = 0;
}

// Hàm vẽ Lakitu lên màn hình
void Latiku::Draw() const
{
    Rectangle src_rec = animation_.Get_Current_Rec();

    if (position_.x > player->getPosition().x)
        src_rec.width = std::abs(src_rec.width);
    else
        src_rec.width = -std::abs(src_rec.width);

    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src_rec.width) * scale_screen,
        src_rec.height * scale_screen};

    DrawTexturePro(animation_.Get_Sprite().sprite, src_rec, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

// Lakitu bị trúng đạn (fireball, v.v.)
void Latiku::Notify_Be_Fired_Or_Hit()
{
    if (state_ != Latiku_State::be_fired_or_hit)
    {
        state_ = Latiku_State::be_fired_or_hit;
        animation_.Set_Rec(Enemies_Sprite::Latiku::be_fired);
        velocity_.y = -Push_Velocity; // Bật lên rồi rơi xuống
        is_dead = 1;
    }
}

bool Latiku::Can_Be_Stomped() const { return false; }

bool Latiku::Can_Be_Fired_Or_Hit() const { return true; }

bool Latiku::Need_Check_Map() const { return false; }

// Cập nhật chuyển động và hành vi bay của Lakitu
void Latiku::Animate_(float dt)
{
    if (state_ != Latiku_State::be_fired_or_hit && state_ != Latiku_State::disappear)
    {
        timer_ += dt;

        // Di chuyển trái/phải quanh người chơi
        if (pos_state)
            pos_to_player += hover_speed;
        else
            pos_to_player -= hover_speed;

        if (pos_to_player > hover_radius || -pos_to_player > hover_radius)
            pos_state = !pos_state;

        float target_pos = player->getPosition().x + pos_to_player;
        Vector2 top_left = GetScreenToWorld2D({0, 0}, camera);
        Vector2 bottom_right = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);

        Rectangle screen_rect_world = {
            top_left.x,
            top_left.y,
            bottom_right.x - top_left.x,
            bottom_right.y - top_left.y};
        if (target_pos - animation_.Get_Current_Rec().width / 2.0f < screen_rect_world.x)
        {
            target_pos = screen_rect_world.x + animation_.Get_Current_Rec().width / 2.0f;
            pos_to_player = target_pos - player->getPosition().x;
            pos_state = !pos_state;
        }
        position_.x = Lerp(position_.x, target_pos, 0.06f);

        position_.y = base_y + sinf(GetTime() * 4.0f) * 5.0f;

        if (state_ == Latiku_State::throw_spiny)
        {
            if (timer_ >= throw_duration)
            {
                Spawn_Spiny();
            }
        }
        else if (timer_ >= throw_interval)
        {
            state_ = Latiku_State::throw_spiny;
            animation_.Set_Rec(Enemies_Sprite::Latiku::throw_);
            timer_ = 0.0f;
        }
    }
}

// Hàm tạo và ném Spiny từ trên xuống
void Latiku::Spawn_Spiny()
{
    Vector2 velo = {75.0f, 0.0f};

    Rectangle player_rec = player->get_draw_rec();

    if (position_.x > player_rec.x + player_rec.width / 2.0f)
        velo.x *= -1;

    Vector2 spawn_pos = {
        position_.x,
        position_.y - animation_.Get_Current_Rec().height * scale_screen / 2.0f};

    Spiny *spiny = new Spiny(spawn_pos, velo);
    enemies->push_back(spiny);
    enemy_map[spiny] = std::vector<Enemy *>();

    state_ = Latiku_State::fly;
    timer_ = 0;
    animation_.Set_Rec(Enemies_Sprite::Latiku::fly_);
}

void Latiku::Disappear_(float dt)
{
    position_.x -= 2.0f;
    position_.y = base_y + sinf(GetTime() * 4.0f) * 5.0f;
}

json Latiku::to_json() const
{
    json j;

    // Thuộc tính kế thừa từ Enemy
    j["position"] = {position_.x, position_.y};
    j["velocity"] = {velocity_.x, velocity_.y};
    j["gravity"] = gravity_;
    j["is_ground"] = is_ground;
    j["is_active"] = is_active;
    j["is_dead"] = is_dead;
    j["first_appear"] = first_appear;

    // Thuộc tính riêng của Latiku
    j["state"] = static_cast<int>(state_);
    j["timer"] = timer_;
    j["pos_to_player"] = pos_to_player;
    j["pos_state"] = pos_state;
    j["base_y"] = base_y;

    return j;
}

void Latiku::from_json(const json &j)
{
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

    // Thuộc tính riêng của Latiku
    state_ = static_cast<Latiku_State>(j.at("state").get<int>());
    timer_ = j.at("timer");
    pos_to_player = j.at("pos_to_player");
    pos_state = j.at("pos_state");
    base_y = j.at("base_y");
}