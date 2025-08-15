#pragma once
#include "Enemy/Enemy.h"

class KoopaState;

class KoopaTroopa : public Enemy
{
    friend class KoopaState;
    friend class KoopaWalkingState;
    friend class KoopaShellIdleState;
    friend class KoopaShellMovingState;
    friend class KoopaDyingState;
    friend class KoopaFlyingState;

private:
    KoopaState *current_state_;
    KoopaState *previous_state;
    Vector2 before_pos_;

public:
    KoopaTroopa(Vector2 pos);
    KoopaTroopa(Vector2 pos, bool is_flying);

    ~KoopaTroopa();

    void Update(float dt) override;
    void Draw() const override;

    void SetState(KoopaState *new_state);

    void Notify_Fall(float dt) override;

    void Notify_Be_Stomped() override;
    void Notify_Be_Fired_Or_Hit() override;
    void Notify_Be_Kicked(int direction) override;

    void Notify_On_Ground() override;
    void Set_Pos(Vector2 pos) override;
    Vector2 Get_Previous_Pos() const override { return before_pos_; }

    bool Can_Be_Stomped() const override { return true; }
    bool Can_Be_Fired_Or_Hit() const override { return true; }
    bool Can_Be_Kicked() const override;

    json to_json() const override ;
    void from_json(const json& j) override;

    bool Kill_Enemy() override;
};
