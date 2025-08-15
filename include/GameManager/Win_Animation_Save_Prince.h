#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "PlayerInformation.h"
#include "I_Win_Animation.h"
#include "Animation.h"

enum class Save_Prince_State
{
    NONE,
    PLAYER_MOVING,
    PRINCE_ESCAPING,
    PRINCE_SAVED,
    UP_SCORE
};

class Win_Animation_Save_Prince : public I_Win_Animation_Manager
{
private:
    PlayerInformation &player_info;
    Player *player;
    Animation kidnap;
    Animation prince;
    Vector2 kidnap_pos;
    Vector2 win_animation_pos;
    float timer_;

    Save_Prince_State cur_state;

public:
    Win_Animation_Save_Prince(Vector2 win_pos, Vector2 pos, PlayerInformation &player_info, Player *player);
    ~Win_Animation_Save_Prince() = default;

    void Update(float dt) override;
    void Draw() const override;
    void Enter_Win_Animation() override;
    bool Check_Win_Animation() override;
    bool End_Animation() override;

    void Set_Player_Animation(Player *player) override;

private:
    void Player_Move();
};
