#pragma once
#include <raylib.h>
#include <vector>
#include "sprite.h"
#include "Constants.h"

class Animation
{
private:
    SpriteSheet* sprite_;            // Ảnh sprite sheet
    std::vector<Rectangle> frames_; // Danh sách frame (các phần cắt của sprite sheet)
    Rectangle current_rec_;         // Frame hiện tại
    int frame_index_;               // Chỉ số frame hiện tại
    float frame_speed_;             // Thời gian mỗi frame (tính bằng giây)
    float elapsed_time_;            // Thời gian đã trôi qua cho frame hiện tại

public:
    Animation(SpriteSheet* sprite);
    Animation(SpriteSheet* sprite, std::vector<Rectangle> frames, float frame_speed);
    Animation(SpriteSheet* sprite, Rectangle rec);
    Animation& operator=(const Animation& other);
    void Update(float deltaTime);
    Rectangle Get_Current_Rec() const;
    SpriteSheet& Get_Sprite() const;
    void Set_Frame(int index);
    int Get_Frame_Index() const;
    int Get_Frame_Count() const;
    void Set_Frames(const std::vector<Rectangle>& frames);
    void Set_Frame_Speed(float speed);
    void Set_Rec(const Rectangle& rec);

    json to_json() const;
    void from_json(const json& j);
};
