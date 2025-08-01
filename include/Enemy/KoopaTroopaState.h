#pragma once
class KoopaTroopa;

class KoopaState {
public:
    virtual ~KoopaState() = default;

    virtual void Enter(KoopaTroopa* koopa) {}
    virtual void Exit(KoopaTroopa* koopa) {}
    virtual void Update(KoopaTroopa* koopa, float dt) = 0;
    virtual void OnStomped(KoopaTroopa* koopa) {}
    virtual void OnFired(KoopaTroopa* koopa) ;
};

// ------ WALKING ------
class KoopaWalkingState : public KoopaState {
public:
    void Enter(KoopaTroopa* koopa) override;
    void Update(KoopaTroopa* koopa, float dt) override;
    void OnStomped(KoopaTroopa* koopa) override;
};

// ------ SHELL IDLE ------
class KoopaShellIdleState : public KoopaState {
public:
    void Enter(KoopaTroopa* koopa) override;
    void Update(KoopaTroopa* koopa, float dt) override;
    void OnStomped(KoopaTroopa* koopa) override; // kick to move
};

// ------ SHELL MOVING ------
class KoopaShellMovingState : public KoopaState {
public:
    void Enter(KoopaTroopa* koopa) override;
    void Update(KoopaTroopa* koopa, float dt) override;
    void OnStomped(KoopaTroopa* koopa) override; // stop movement
};

// ------ DYING ------
class KoopaDyingState : public KoopaState {
private:
    float dying_down_timer = 3.0f;
    float dying_up_timer = 0.2f;

public:
    void Enter(KoopaTroopa* koopa) override;
    void Update(KoopaTroopa* koopa, float dt) override;
};

// ------ FLYING ------
class KoopaFlyingState : public KoopaState {
private:
    float fly_timer = 0.0f;
    float fly_interval = 10.5f;
    float fly_speed = 400.0f;

public:
    void Enter(KoopaTroopa* koopa) override;
    void Update(KoopaTroopa* koopa, float dt) override;
    void OnStomped(KoopaTroopa* koopa) override;
};