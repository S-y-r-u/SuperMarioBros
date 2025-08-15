#include "GameManager/DrawScore.h"
#include <iostream>

DrawScoreUp::DrawScoreUp(const Vector2 &position, int score)
    : position_(position), score_(score), frame_timer(0.0f), is_delete(false) {}

void DrawScoreUp::Update()
{
    frame_timer += GetFrameTime();
    if (frame_timer >= time_interval)
    {
        is_delete = true;
    }
    position_.y -= animation_speed;
}

void DrawScoreUp::Draw()
{
    if (is_delete)
        return;
    Font_Sprite::DrawText(std::to_string(score_), position_.x, position_.y, WHITE);
}

bool DrawScoreUp::Is_Delete() const
{
    return is_delete;
}

void Score_Manager::AddScore(const Vector2 &position, int score)
{
    scores_.emplace_back(std::make_unique<DrawScoreUp>(position, score));
}
void Score_Manager::Update()
{
    for (auto &score : scores_)
    {
        score->Update();
    }
    RemoveDeletedScores();
}

void Score_Manager::Draw()
{
    for (auto &score : scores_)
    {
        score->Draw();
    }
}
void Score_Manager::RemoveDeletedScores()
{
    for (int i = static_cast<int>(scores_.size()) - 1; i >= 0; --i)
    {
        if (scores_[i]->Is_Delete())
        {
            scores_.erase(scores_.begin() + i);
        }
    }
}

void Score_Manager::ClearScores()
{
    scores_.clear();
}
