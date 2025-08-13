
#pragma once
#include "raylib.h"
#include "Constants.h"
#include "sprite.h"
#include "GameManager/Animation.h"
#include <cmath>
#include <vector>

class RotatingBar
{
private:
    Vector2 pivot;                      // Điểm cố định
    float length;                        // Chiều dài thanh trong game (pixel trên màn hình)
    float angle;                         // Góc hiện tại (độ)
    float speed;                         // Tốc độ quay (độ/giây)
    Animation animation_;              // Animation cho thanh quay

public:
    RotatingBar(Vector2 pivotPos);

    void Update(float dt);
    void Draw() const;

    bool CheckCollision(Rectangle rect) const;

    Vector2 GetPivot() const;
    Vector2 GetEndPoint() const;

        // Serialize/Deserialize
    json to_json() const;
    void from_json(const json& j);
};