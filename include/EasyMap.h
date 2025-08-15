#pragma once
#include "Stage.h"
#include "GameManager/Win_Animation_Climb_Flag.h"
#include <fstream>
#include <string>

class EasyMap : public Stage
{
public:
    EasyMap(PlayerInformation& info, Player& player);
    ~EasyMap();
};