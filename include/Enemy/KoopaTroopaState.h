#pragma once
#include "Enemy.h"
class KoopaTroopa;

class KoopaState
{
public:
    virtual ~KoopaState() = default;

    virtual void Enter(KoopaTroopa *koopa) {}
    virtual void Update(KoopaTroopa *koopa, float dt) = 0;
    virtual void OnStomped(KoopaTroopa *koopa) {}
    virtual void OnFired(KoopaTroopa *koopa);
    virtual void OnKicked(KoopaTroopa *koopa, int direction) {}
};

// ------ WALKING ------
class KoopaWalkingState : public KoopaState
{
public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa) override;
};

// ------ SHELL IDLE ------
class KoopaShellIdleState : public KoopaState
{
private:
    const float InChange_Frame_Time = 1.0f; // seconds
    float immobile_timer = 0.0f;
    float timer;

public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    float GetTimer() const { return timer; }
    void SetTimer(float t) { timer = t; }
    void OnStomped(KoopaTroopa *koopa) override; // kick to move
    void OnKicked(KoopaTroopa *koopa, int direction) override;
};

// ------ SHELL MOVING ------
class KoopaShellMovingState : public KoopaState
{
private:
public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
    void OnStomped(KoopaTroopa *koopa) override; // stop movement
};

// ------ DYING ------
class KoopaDyingState : public KoopaState
{
public:
    void Enter(KoopaTroopa *koopa) override;
    void Update(KoopaTroopa *koopa, float dt) override;
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
    float GetFlyingTimer() const { return fly_timer; }
    void SetFlyingTimer(float timer) { fly_timer = timer; }
    void OnStomped(KoopaTroopa *koopa) override;
};