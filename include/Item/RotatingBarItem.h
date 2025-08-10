#pragma once
#include "raylib.h"
#include "Constants.h"
#include "sprite.h"
#include <cmath>
#include <vector>

class RotatingBar
{
private:
    Vector2 pivot;                      // Điểm cố định
    float length;                        // Chiều dài thanh trong game (pixel trên màn hình)
    float angle;                         // Góc hiện tại (độ)
    float speed;                         // Tốc độ quay (độ/giây)
    const SpriteSheet& sprite_;           // Sprite sheet chứa 4 frame
    std::vector<Rectangle> frames;       // Các frame sourceRec
    int currentFrame;                    // Frame hiện tại
    float frameTime;                      // Thời gian giữa mỗi frame
    float frameCounter;                   // Đếm thời gian để đổi frame

public:
    RotatingBar(Vector2 pivotPos, float length, float speed);

    void Update(float dt);
    void Draw() const;

    bool CheckCollision(Rectangle rect) const;

    Vector2 GetPivot() const;
    Vector2 GetEndPoint() const;
};