#include "DrawScore.h"
#include <iostream>

DrawScore::DrawScore(const Vector2 &position, int score)
    : position_(position), score_(score), frame_timer(0.0f), is_delete(false) {}

void DrawScore::Update()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= time_interval)
    {
        is_delete = true;
    }
    position_.y -= animation_speed;
}

void DrawScore::Draw()
{
    if (is_delete)
        return;
    Font_Sprite::DrawText(std::to_string(score_), position_.x, position_.y, WHITE);
}

bool DrawScore::Is_Delete() const
{
    return is_delete;
}

void Score_Manager::AddScore(const Vector2 &position, int score)
{
    scores_.emplace_back(position, score);
}
void Score_Manager::Update()
{
    for (auto &score : scores_)
    {
        score.Update();
    }
    RemoveDeletedScores();
}

void Score_Manager::Draw()
{
    for (auto &score : scores_)
    {
        score.Draw();
    }
}
void Score_Manager::RemoveDeletedScores()
{
    for (auto it = scores_.begin(); it != scores_.end();)
    {
        if (it->Is_Delete())
            it = scores_.erase(it); // trả về iterator mới
        else
            ++it;
    }
}
