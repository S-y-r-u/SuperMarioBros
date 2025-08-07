#pragma once
#include "Stage.h"
#include <fstream>

class MediumMap : public Stage {
    public:
        MediumMap(Player_Mode mode, PlayerInformation& info);
        ~MediumMap();
};