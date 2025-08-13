#include "GameManager/Animation.h"

Animation::Animation(SpriteSheet *sprite)
    : sprite_(sprite),
      frames_(),
      current_rec_(),
      frame_index_(0),
      frame_speed_(0.1f),
      elapsed_time_(0.0f) {}

// --------------------------------------
// Constructor khởi tạo với dữ liệu sẵn có
// --------------------------------------
Animation::Animation(SpriteSheet *sprite, std::vector<Rectangle> frames, float frame_speed)
    : sprite_(sprite),
      frames_(frames),
      frame_index_(0),
      frame_speed_(frame_speed),
      elapsed_time_(0.0f)
{
    current_rec_ = frames[frame_index_];
}

Animation::Animation(SpriteSheet *sprite, Rectangle rec)
    : sprite_(sprite),
      current_rec_(rec),
      frame_index_(0),
      frame_speed_(0.1f),
      elapsed_time_(0.0f)
{
    frames_.push_back(rec);
}

Animation &Animation::operator=(const Animation &other)
{
    if (this != &other) // tránh tự gán chính nó
    {
        sprite_ = other.sprite_;
        frames_ = other.frames_;
        current_rec_ = other.current_rec_;
        frame_index_ = other.frame_index_;
        frame_speed_ = other.frame_speed_;
        elapsed_time_ = other.elapsed_time_;
    }
    return *this;
}

// ---------------------
// Cập nhật animation
// ---------------------
void Animation::Update(float deltaTime)
{
    if (frames_.empty())
        return;

    elapsed_time_ += deltaTime;
    if (elapsed_time_ >= frame_speed_)
    {
        elapsed_time_ = 0.0f;
        frame_index_ = (frame_index_ + 1) % frames_.size();
        current_rec_ = frames_[frame_index_];
    }
}

// ---------------------
// Lấy Rectangle hiện tại
// ---------------------
Rectangle Animation::Get_Current_Rec() const
{
    return current_rec_;
}

SpriteSheet &Animation::Get_Sprite() const
{
    return *sprite_;
}

// ---------------------
// Đặt frame thủ công
// ---------------------
void Animation::Set_Frame(int index)
{
    if (index >= 0 && index < (int)frames_.size())
    {
        frame_index_ = index;
        current_rec_ = frames_[frame_index_];
        elapsed_time_ = 0.0f;
    }
}

// ---------------------
// Lấy index frame hiện tại
// ---------------------
int Animation::Get_Frame_Index() const
{
    return frame_index_;
}

// ---------------------
// Lấy tổng số frame
// ---------------------
int Animation::Get_Frame_Count() const
{
    return (int)frames_.size();
}

// ---------------------
// Gán danh sách frames mới
// ---------------------
void Animation::Set_Frames(const std::vector<Rectangle> &frames)
{
    frames_ = frames;
    frame_index_ = 0;
    elapsed_time_ = 0.0f;
    if (!frames_.empty())
        current_rec_ = frames_[0];
}

void Animation::Set_Rec(const Rectangle &rec)
{
    current_rec_ = rec;
    frames_.clear();
    frames_.push_back(rec);
    frame_index_ = 0;
    elapsed_time_ = 0.0f;
}

void Animation::Set_Frame_Speed(float speed)
{
    frame_speed_ = speed;
}


// ---------------------
// JSON serialization
// ---------------------
json Animation::to_json() const {
    json j;
    // Không serialize sprite_ (con trỏ), chỉ serialize index frame, speed, elapsed, frames
    j["frame_index"] = frame_index_;
    j["frame_speed"] = frame_speed_;
    j["elapsed_time"] = elapsed_time_;
    // Serialize frames_
    j["frames"] = json::array();
    for (const auto& rec : frames_) {
        j["frames"].push_back({rec.x, rec.y, rec.width, rec.height});
    }
    // Serialize current_rec_
    j["current_rec"] = {current_rec_.x, current_rec_.y, current_rec_.width, current_rec_.height};
    return j;
}

void Animation::from_json(const json& j) {
    frame_index_ = j.value("frame_index", 0);
    frame_speed_ = j.value("frame_speed", 0.1f);
    elapsed_time_ = j.value("elapsed_time", 0.0f);
    // Deserialize frames_
    frames_.clear();
    if (j.contains("frames")) {
        for (const auto& arr : j["frames"]) {
            if (arr.is_array() && arr.size() == 4) {
                frames_.push_back({arr[0], arr[1], arr[2], arr[3]});
            }
        }
    }
    // Deserialize current_rec_
    if (j.contains("current_rec")) {
        auto arr = j["current_rec"];
        if (arr.is_array() && arr.size() == 4) {
            current_rec_ = {arr[0], arr[1], arr[2], arr[3]};
        }
    }
}