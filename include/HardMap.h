#pragma once
#include "Stage.h"
#include "GameManager/Win_Animation_Save_Prince.h"
#include <fstream>

class HardMap : public Stage {
    public:
        HardMap(PlayerInformation& info, Player& player);
        ~HardMap();
};