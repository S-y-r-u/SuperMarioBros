#pragma once
#include "Enemy.h"
class KoopaTroopa;

class KoopaState
{
public:
    virtual ~KoopaState() = default;

    virtual void Enter(KoopaTroopa *koopa) {}
    virtual void Update(KoopaTroopa *koopa, float dt) = 0;
    virtual void OnStomped(KoopaTroopa *koopa, PlayerInformation &info) {}
    virtual void OnFired(KoopaTroopa *koopa);
    virtual void OnKicked(KoopaTroopa *koopa , int direction , PlayerInformation &info) {}
    virtual int Get_Score() const = 0;
};

// ------ WALKING ------
class KoopaWalkingState : public KoopaState
{
private:
    const int Score_Walking = 100;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa, PlayerInformation &info) override;
    int Get_Score() const override { return Score_Walking; }
};

// ------ SHELL IDLE ------
class KoopaShellIdleState : public KoopaState
{
private:
    const int Score_Shell = 100;
    const float InChange_Frame_Time = 1.0f; // seconds
    float immobile_timer = 0.0f;
    float timer;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa, PlayerInformation &info) override; // kick to move
    void OnKicked(KoopaTroopa *koopa , int direction , PlayerInformation &info) override;
    int Get_Score() const override { return Score_Shell; }
    float GetTimer() const { return timer; }
    void SetTimer(float t) { timer = t; }
};

// ------ SHELL MOVING ------
class KoopaShellMovingState : public KoopaState
{
private:
    const int Score_Kicked = 100;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa, PlayerInformation &info) override; // stop movement
    int Get_Score() const override { return Score_Kicked; }
};

// ------ DYING ------
class KoopaDyingState : public KoopaState
{
private:
    const int Score_Dying_Walking = 200;
    const int Score_Dying_Flying = 300;
    const int Score_Dying_Shell = 100; 
    int score_;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    int Get_Score() const override { return score_; }
};

// ------ FLYING ------
class KoopaFlyingState : public KoopaState
{
private:
    float fly_timer = 0.0f;
    const float fly_interval = 10.5f;
    const float fly_speed = 240.0f;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa , PlayerInformation &info) override;
    int Get_Score() const override { return 0; }
    float GetFlyingTimer() const { return fly_timer; }
    void SetFlyingTimer(float timer) { fly_timer = timer; }
};