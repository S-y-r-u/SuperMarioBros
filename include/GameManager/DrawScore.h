#pragma once
#include "sprite.h"
#include <memory>

class I_DrawScore
{
public:
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual bool Is_Delete() const = 0;
};

class DrawScoreUp : public I_DrawScore
{
private:
    Vector2 position_;
    int score_;
    float time_interval = 0.75f;
    float frame_timer;
    float animation_speed = 0.75f;
    bool is_delete;

public:
    DrawScoreUp(const Vector2 &position, int score);
    void Update() override;
    void Draw() override;
    bool Is_Delete() const override;
};

class Score_Manager
{
private:
    std::vector<std::unique_ptr<I_DrawScore>> scores_;
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
    void ClearScores();
};
