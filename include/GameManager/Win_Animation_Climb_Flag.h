#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "PlayerInformation.h"
#include "DrawScore.h"
#include "I_Win_Animation.h"
#include "Flag/Flag_Pole.h"
#include "Flag/Flag_Castle.h"

enum class Win_Animation_State
{
    None,
    Climbing,
    Preparing,
    Going,
    Posing,
    Fading,
    Raising,
    UpScore
};

class Win_Animation_Climb_Flag : public I_Win_Animation_Manager
{
public:
    Win_Animation_Climb_Flag(Player *player, Vector2 flag_pole, Vector2 flag_castle, PlayerInformation &player_info);
    ~Win_Animation_Climb_Flag();

    void Update(float dt) override;
    void Draw() const override;
    void Enter_Win_Animation() override;
    bool Check_Win_Animation() override;
    bool End_Animation() override;

private:
    Player *player_;
    Flag_Pole *flag_pole_;
    Flag_Castle *flag_castle_;
    PlayerInformation &player_info_;

    const float Flag_Top_Y = 144.0f;
    const float Flag_Bottom_Y = 528.0f;
    float Flag_Pos_X;
    float Mario_Base_Y;
    float Castle_Door_X;

    int bonus_points;
    const float Slide_Speed = 150.0f;
    const float Walk_Speed = 300.0f;
    float frame_timer;
    const float Cool_Down_Time = 1.0f;

    Win_Animation_State current_state;

    int Calculate_Bonus_Points();
    void Climb_Flag_Pole();
    void Prepare_To_Castle();
    void Go_To_Castle();
    void Pose();
    void Fade_Out();
    void Raise_Flag();

    void Set_Player_Animation(Player *player) override;
};
