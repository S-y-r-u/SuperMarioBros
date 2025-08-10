#include "Item/RotatingBarItem.h"

RotatingBar::RotatingBar(Vector2 pivotPos, float length, float speed): pivot(pivotPos), length(length), angle(0), speed(speed),
      sprite_(Item_Sprite::item_), frames(Item_Sprite::Fire_Ball::Fly::fly_), currentFrame(0),
      frameTime(0.3f), frameCounter(0.0f)
{
}

void RotatingBar::Update(float dt)
{
    // Cập nhật góc quay
    angle += speed * dt;
    if (angle >= 360.0f) angle -= 360.0f;

    // Cập nhật frame animation
    frameCounter += dt;
    if (frameCounter >= frameTime)
    {
        frameCounter -= frameTime;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void RotatingBar::Draw() const
{
    Rectangle sourceRec = frames[currentFrame];
    float tileW = sourceRec.width;
    float tileH = sourceRec.height;

    int numTiles = (int)ceil(length / (tileW * scale_screen));

    for (int i = 0; i < numTiles; i++)
    {
        // Offset trước khi xoay
        Vector2 offset = { i * tileW * scale_screen, 0 };

        // Xoay offset
        float rad = DEG2RAD * angle;
        Vector2 rotatedOffset = {
            offset.x * cosf(rad) - offset.y * sinf(rad),
            offset.x * sinf(rad) + offset.y * cosf(rad)
        };

        Vector2 tilePos = { pivot.x + rotatedOffset.x, pivot.y + rotatedOffset.y };

        Rectangle destRec = { tilePos.x, tilePos.y, tileW * scale_screen, tileH * scale_screen };
        Vector2 origin = { 0, destRec.height / 2.0f };

        DrawTexturePro(sprite_.sprite, sourceRec, destRec, origin, angle, WHITE);
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
        {rect.x, rect.y + rect.height}
    };

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
        pivot.y + sinf(DEG2RAD * angle) * length
    };
}
