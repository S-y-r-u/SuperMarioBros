#pragma once
#include "GameManager/I_Stage.h"
#include "GameManager/PlayerInformation.h"
#include "Constants.h"

class Intro_Animation : public I_Stage
{
protected:
    Texture2D intro_;
    PlayerInformation &player_info;
    Player_Mode player_mode;
    float timer_;
    const float End_Intro = 2.0f;

public:
    Intro_Animation(PlayerInformation &info, Player_Mode mode);
    virtual ~Intro_Animation() {}
};