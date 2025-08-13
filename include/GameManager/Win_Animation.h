#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "PlayerInformation.h"
#include "DrawScore.h"
#include "Flag/Flag_Pole.h"
#include "Flag/Flag_Castle.h"

class Win_Animation_Manager
{
public:
    Win_Animation_Manager(Player &player, Flag_Pole &flag_pole, Flag_Castle &flag_castle, PlayerInformation &player_info);
    void Update(float dt);
    void Enter_Win_Animation();
    bool Check_Win_Animation();
    bool End_Animation();
    bool Player_Disappear();

    json to_json() const;
    void from_json(const json& j);
private:
    Player &player_;
    Flag_Pole &flag_pole_;
    Flag_Castle &flag_castle_;
    PlayerInformation &player_info_;
    const float Flag_Top_y = 144.0f;
    const float Flag_Bottom_y = 528.0f;
    float Flag_Pos_X;
    float mario_base_y;
    float Castle_Door_X;
    int bonus_points;
    const float Slide_Speed = 150.0f;
    const float Walk_Speed = 300.0f;
    bool preparing_to_castle;
    bool go_to_castle;
    bool is_climbing;
    float frame_timer;
    bool is_pose;
    bool is_fade_out;
    bool flag_raise;
    bool player_disappear;
    const float Cool_Down_Time = 1.0f;
    int Calculate_Bonus_Points();
    void Climb_Flag_Pole();
    void Prepare_To_Castle();
    void Go_To_Castle();
    void Pose();
    void Fade_Out();
    void Raise_Flag();
};
