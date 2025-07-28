#include "Enemy/Latiku.h"

// Constructor: khởi tạo Latiku với vị trí, trọng lực, con trỏ tới Player và danh sách kẻ địch
Latiku::Latiku(Vector2 pos, float gravity, Player *player, std::vector<Enemy *> *enemies)
    : Enemy(pos, {120.0f, 0}, gravity), // Tốc độ mặc định khi spawn
      player(player),                   // Lưu con trỏ tới người chơi
      state_(Latiku_State::fly),        // Trạng thái ban đầu là bay
      enemies(enemies),                 // Danh sách các Enemy để spawn Spiny
      base_y(pos.y),                    // Ghi nhớ tọa độ Y gốc để bay dao động quanh
      pos_state(0),                     // Trạng thái điều khiển hướng bay trái/phải
      timer_(0.0f),                     // Bộ đếm thời gian dùng cho hành vi ném
      before_pos(pos),                  // Lưu vị trí ban đầu để rơi khi bị đánh
      delta_time(0.0f),                 // Biến thời gian rơi
      pos_to_player(hover_radius_front) // Vị trí bay phía trước người chơi ban đầu
{
    rec_ = Enemies_Sprite::Latiku::fly_; // Frame sprite mặc định là đang bay
}

// Hàm cập nhật trạng thái mỗi frame
void Latiku::Update(float dt)
{
    Be_Fired_Or_Hit(); // Nếu bị đánh thì xử lý rơi
    Animate_(dt);      // Cập nhật chuyển động, hành vi

    // Nếu rơi khỏi màn hình thì vô hiệu hóa
    if (position_.y - rec_.height >= Screen_h)
        is_active = 0;
}

// Hàm vẽ Lakitu lên màn hình
void Latiku::Draw() const
{
    Rectangle src_rec = rec_; // Rectangle gốc lấy từ sprite sheet

    // Lật hình nếu đang ở bên phải người chơi (nhìn về trái)
    if (position_.x > player->getPosition().x + player->get_draw_rec().width / 2.0f)
        src_rec.width = std::abs(src_rec.width);
    else
        src_rec.width = -std::abs(src_rec.width); // Nhìn về phải

    // Tọa độ đích sau khi scale
    Rectangle dest = {
        position_.x,
        position_.y,
        std::abs(src_rec.width) * scale_screen,
        src_rec.height * scale_screen};

    // Vẽ Lakitu
    DrawTexturePro(sprite_.sprite, src_rec, dest, {dest.width / 2.0f, dest.height}, 0.0f, WHITE);
}

// Lakitu bị trúng đạn (fireball, v.v.)
void Latiku::Notify_Be_Fired_Or_Hit()
{
    if (state_ != Latiku_State::be_fired_or_hit)
    {
        state_ = Latiku_State::be_fired_or_hit;  // Chuyển trạng thái
        rec_ = Enemies_Sprite::Latiku::be_fired; // Đổi frame ảnh
        before_pos = position_;                  // Lưu vị trí rơi ban đầu
        delta_time = 0.0f;                       // Reset thời gian rơi
        is_dead = 1;                             // Đánh dấu đã chết
    }
}

// Lakitu miễn nhiễm với stomp
bool Latiku::Can_Be_Stomped() const { return false; }

// Lakitu có thể bị đánh (fireball, đạn...)
bool Latiku::Can_Be_Fired_Or_Hit() const { return true; }

// Cập nhật chuyển động và hành vi bay của Lakitu
void Latiku::Animate_(float dt)
{
    // Nếu không bị đánh thì mới thực hiện hành vi bay và ném
    if (state_ != Latiku_State::be_fired_or_hit)
    {
        timer_ += dt; // Tăng thời gian để điều khiển hành vi

        // ✅ Di chuyển trái/phải quanh người chơi
        if (pos_state)
            pos_to_player += hover_speed;
        else
            pos_to_player -= hover_speed;

        // Nếu đã tới giới hạn khoảng cách thì đổi hướng
        if (pos_to_player > hover_radius_front || -pos_to_player > hover_radius_back)
            pos_state = !pos_state;

        // Di chuyển tới vị trí mới bằng nội suy Lerp (mượt)
        position_.x = Lerp(position_.x, player->getPosition().x + pos_to_player, 0.12f);

        // Bay dao động theo sin trên trục Y
        position_.y = base_y + sinf(GetTime() * 4.0f) * 5.0f;

        // ✅ Xử lý trạng thái ném Spiny
        if (state_ == Latiku_State::throw_spiny)
        {
            if (timer_ >= throw_duration)
            {
                Spawn_Spiny(); // Nếu đến lúc thì ném
            }
        }
        else if (timer_ >= throw_interval)
        {
            state_ = Latiku_State::throw_spiny;    // Chuyển sang trạng thái ném
            rec_ = Enemies_Sprite::Latiku::throw_; // Đổi frame ảnh ném
            timer_ = 0.0f;                         // Reset timer
        }
    }
}

// Xử lý rơi tự do khi bị đánh trúng
void Latiku::Be_Fired_Or_Hit()
{
    if (state_ == Latiku_State::be_fired_or_hit)
    {
        delta_time += 0.12f;

        // Phương trình rơi tự do: y = y0 + v0*t + 0.5*g*t^2
        float deltaY = -Push_Height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
        position_.y = before_pos.y + deltaY;
    }
}

// Hàm tạo và ném Spiny từ trên xuống
void Latiku::Spawn_Spiny()
{
    // ✅ Tạo vận tốc ban đầu cho Spiny
    Vector2 velo = {120.0f, 0.0f};

    // Nếu Lakitu ở bên phải Mario thì Spiny ném qua trái
    if (position_.x > player->getPosition().x + player->get_draw_rec().width / 2.0f)
        velo.x *= -1;

    // Tính toán vị trí spawn ngay dưới Lakitu
    Vector2 spawn_pos = {
        position_.x,
        position_.y - rec_.height * scale_screen / 2.0f};

    // Tạo mới Spiny và thêm vào danh sách enemy
    enemies->push_back(new Spiny(spawn_pos, velo, 0.0f));

    // Reset lại trạng thái về bay
    state_ = Latiku_State::fly;
    timer_ = 0;
    rec_ = Enemies_Sprite::Latiku::fly_;
}
