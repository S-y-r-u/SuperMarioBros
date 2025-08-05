#include "Enemy/Latiku.h"
#include <raymath.h>

// Constructor: khởi tạo Latiku với vị trí, trọng lực, con trỏ tới Player và danh sách kẻ địch
Latiku::Latiku(Vector2 pos, Player *player, std::vector<Enemy *> *enemies, std::unordered_map<Enemy *, std::vector<Enemy *>> &enemy_map)
    : Enemy(pos, {120.0f, 0}, 0.0f),
      player(player),
      state_(Latiku_State::fly),
      enemies(enemies),
      base_y(pos.y),
      pos_state(0),
      timer_(0.0f),
      pos_to_player(hover_radius_front),
      enemy_map(enemy_map)
{
    rec_ = Enemies_Sprite::Latiku::fly_;
}

// Hàm cập nhật trạng thái mỗi frame
void Latiku::Update(float dt)
{
    if (state_ == Latiku_State::be_fired_or_hit)
    {
        velocity_.y += Physics::gravity_ * dt;
        position_.y += velocity_.y * dt;
    }
    else
    {
        Animate_(dt);
    }

    if (position_.y - rec_.height >= Screen_h)
        is_active = 0;
}

// Hàm vẽ Lakitu lên màn hình
void Latiku::Draw() const
{
    Rectangle src_rec = rec_;

    if (position_.x > player->getPosition().x + player->get_draw_rec().width / 2.0f)
        src_rec.width = std::abs(src_rec.width);
    else
        src_rec.width = -std::abs(src_rec.width);

    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src_rec.width) * scale_screen,
        src_rec.height * scale_screen};

    DrawTexturePro(sprite_.sprite, src_rec, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

// Lakitu bị trúng đạn (fireball, v.v.)
void Latiku::Notify_Be_Fired_Or_Hit(PlayerInformation &info)
{
    if (state_ != Latiku_State::be_fired_or_hit)
    {
        info.UpdateScore(Score_Latiku);
        Score_Manager &score_manager = Score_Manager::GetInstance();
        Rectangle dest_rec = Get_Draw_Rec();
        score_manager.AddScore({dest_rec.x, dest_rec.y}, Score_Latiku);
        state_ = Latiku_State::be_fired_or_hit;
        rec_ = Enemies_Sprite::Latiku::be_fired;
        velocity_.y = -Push_Velocity; // Bật lên rồi rơi xuống
        is_dead = 1;
    }
}

bool Latiku::Can_Be_Stomped() const { return false; }

bool Latiku::Can_Be_Fired_Or_Hit() const { return true; }

bool Latiku::Need_Check_Ground_Block() const { return false; }

// Cập nhật chuyển động và hành vi bay của Lakitu
void Latiku::Animate_(float dt)
{
    if (state_ != Latiku_State::be_fired_or_hit)
    {
        timer_ += dt;

        // Di chuyển trái/phải quanh người chơi
        if (pos_state)
            pos_to_player += hover_speed;
        else
            pos_to_player -= hover_speed;

        if (pos_to_player > hover_radius_front || -pos_to_player > hover_radius_back)
            pos_state = !pos_state;

        float target_pos = player->getPosition().x + pos_to_player;
        if (player->getPosition().x + pos_to_player < rec_.width / 2.0f ||
            player->getPosition().x + pos_to_player > 214 * 48.0f - rec_.width / 2.0f)
        {
            target_pos = Clamp(target_pos, rec_.width / 2.0f, 214 * 48.0f - rec_.width / 2.0f);
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
            rec_ = Enemies_Sprite::Latiku::throw_;
            timer_ = 0.0f;
        }
    }
}

// Hàm tạo và ném Spiny từ trên xuống
void Latiku::Spawn_Spiny()
{
    Vector2 velo = {75.0f, 0.0f};

    if (position_.x > player->getPosition().x + player->get_draw_rec().width / 2.0f)
        velo.x *= -1;

    Vector2 spawn_pos = {
        position_.x,
        position_.y - rec_.height * scale_screen / 2.0f};

    Spiny *spiny = new Spiny(spawn_pos, velo);
    enemies->push_back(spiny);
    enemy_map[spiny] = std::vector<Enemy *>();

    state_ = Latiku_State::fly;
    timer_ = 0;
    rec_ = Enemies_Sprite::Latiku::fly_;
}

bool Latiku::Need_Check_Collision_With_Other_Enemy() const
{
    return false;
}