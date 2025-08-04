#pragma once
#include "sprite.h"

class DrawScore
{
private:
    Vector2 position_;
    int score_;
    float time_interval = 0.75f;
    float frame_timer;
    float animation_speed = 0.75f;
    bool is_delete;

public:
    DrawScore(const Vector2 &position, int score);
    void Update();
    void Draw();
    bool Is_Delete() const;
};

class Score_Manager
{
private:
    std::vector<DrawScore> scores_;
    Score_Manager() = default;  
    Score_Manager(const Score_Manager &) = delete;
    Score_Manager &operator=(const Score_Manager &) = delete;

public:
    static Score_Manager &GetInstance()
    {
        static Score_Manager instance;
        return instance;
    }

public:
    void AddScore(const Vector2 &position, int score);
    void Update();
    void Draw();
    void RemoveDeletedScores();
};
