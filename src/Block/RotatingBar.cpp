
#include "Block/RotatingBar.h"

RotatingBar::RotatingBar(Vector2 pivotPos)
    : animation_(&Item_Sprite::item_, Item_Sprite::Fire_Ball::Fly::fly_, 1 / 6.0f),
      pivot(pivotPos),
      length(150.0f),
      angle(0),
      speed(45.0f) {}

void RotatingBar::Update(float dt)
{
    // Cập nhật góc quay
    angle += speed * dt;
    if (angle >= 360.0f)
        angle -= 360.0f;

    // Cập nhật frame animation
    animation_.Update(dt);
}

void RotatingBar::Draw() const
{
    Rectangle sourceRec = animation_.Get_Current_Rec();
    float tileW = sourceRec.width;
    float tileH = sourceRec.height;

    int numTiles = (int)ceil(length / (tileW * scale_screen));

    for (int i = 0; i < numTiles; i++)
    {
        // Offset trước khi xoay
        Vector2 offset = {i * tileW * scale_screen, 0};

        // Xoay offset
        float rad = DEG2RAD * angle;
        Vector2 rotatedOffset = {
            offset.x * cosf(rad) - offset.y * sinf(rad),
            offset.x * sinf(rad) + offset.y * cosf(rad)};

        Vector2 tilePos = {pivot.x + rotatedOffset.x, pivot.y + rotatedOffset.y};

        Rectangle destRec = {tilePos.x, tilePos.y, tileW * scale_screen, tileH * scale_screen};
        Vector2 origin = {0, destRec.height / 2.0f};

        DrawTexturePro(animation_.Get_Sprite().sprite, sourceRec, destRec, origin, angle, WHITE);
    }

    // Debug pivot
    DrawCircleV(pivot, 3, BLACK);
}

bool RotatingBar::CheckCollision(Rectangle rect) const
{
    Vector2 endPoint = GetEndPoint();

    Vector2 rectPoints[4] = {
        {rect.x, rect.y},
        {rect.x + rect.width, rect.y},
        {rect.x + rect.width, rect.y + rect.height},
        {rect.x, rect.y + rect.height}};

    for (int i = 0; i < 4; i++)
    {
        Vector2 a = rectPoints[i];
        Vector2 b = rectPoints[(i + 1) % 4];
        if (CheckCollisionLines(pivot, endPoint, a, b, nullptr))
            return true;
    }

    if (CheckCollisionPointRec(pivot, rect) || CheckCollisionPointRec(endPoint, rect))
        return true;

    return false;
}

Vector2 RotatingBar::GetPivot() const
{
    return pivot;
}

Vector2 RotatingBar::GetEndPoint() const
{
    return {
        pivot.x + cosf(DEG2RAD * angle) * length,
        pivot.y + sinf(DEG2RAD * angle) * length};
}

// Serialize RotatingBar
json RotatingBar::to_json() const {
    json j;
    j["pivot"] = {pivot.x, pivot.y};
    j["length"] = length;
    j["angle"] = angle;
    j["speed"] = speed;
    j["animation"] = animation_.to_json();
    return j;
}

void RotatingBar::from_json(const json& j) {
    pivot.x = j["pivot"][0];
    pivot.y = j["pivot"][1];
    length = j.value("length", 150.0f);
    angle = j.value("angle", 0.0f);
    speed = j.value("speed", 45.0f);
    if (j.contains("animation")) animation_.from_json(j["animation"]);
}