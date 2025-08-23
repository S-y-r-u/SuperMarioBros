#pragma once
#include "Stage.h"
#include "GameManager/Win_Animation_Save_Prince.h"
#include "Platform/Vertical_Platform.h"
#include <fstream>

class HardMap : public Stage
{
private:
    std::vector<I_Platform *> up_platforms;
    std::vector<I_Platform *> down_platforms;

public:
    HardMap(PlayerInformation &info, Player *&player);
    void Run() override;
    void Draw() override;
    ~HardMap();

private:
    void Spawn_Platform();
    void Check_Player_Platform();
};