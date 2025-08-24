#pragma once
#include "Stage.h"
#include "GameManager/Win_Animation_Climb_Flag.h"
#include <fstream>

class MediumMap : public Stage
{
public:
    MediumMap(PlayerInformation &info, Player *&player, Player_Mode &player_mode);
    ~MediumMap();
};