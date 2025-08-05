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
    std::vector<Rectangle> walking_frames_ = Enemies_Sprite::Troopa_Green::Normal::normal_;
    std::vector<Rectangle> shell_idle_frames_ = Enemies_Sprite::Troopa_Green::Shell_Idle::shell_idle;
    std::vector<Rectangle> shell_moving_frames_ = Enemies_Sprite::Troopa_Green::Shell_Moving::shell_moving;
    std::vector<Rectangle> flying_frames_ = Enemies_Sprite::Troopa_Green::Flying::flying_;
    Rectangle be_dying_frame_ = Enemies_Sprite::Troopa_Green::be_dying;
    Vector2 before_pos_;

public:
    KoopaTroopa(Vector2 pos);
    KoopaTroopa(Vector2 pos, bool is_flying);

    ~KoopaTroopa();

    void Update(float dt) override;
    void Draw() const override;

    void SetState(KoopaState *new_state);

    void Notify_Fall(float dt) override;
    void Notify_Be_Stomped(PlayerInformation& info) override;
    void Notify_Be_Fired_Or_Hit(PlayerInformation& info) override;
    void Notify_Be_Kicked(int direction, PlayerInformation& info) override;
    void Notify_On_Ground() override;
    void Set_Pos(Vector2 pos) override;
    Vector2 Get_Previous_Pos() const override { return before_pos_; }

    bool Can_Be_Stomped() const override { return true; }
    bool Can_Be_Fired_Or_Hit() const override { return true; }
    bool Can_Be_Kicked() const override;
    bool Kill_Other_Enemies() const override;
    void Collision_With_Other_Enemy(Vector2 velo, Vector2 pos) override;
};
