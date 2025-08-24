#pragma once
#include "Stage.h"
#include "GameManager/Win_Animation_Save_Prince.h"
#include "Platform/Vertical_Platform.h"
#include "Block/Fire_Block.h"
#include <fstream>

class HardMap : public Stage
{
private:
    std::vector<I_Platform *> up_platforms;
    std::vector<I_Platform *> down_platforms;
    std::vector<Fire_Block *> fire_blocks;

public:
    HardMap(PlayerInformation &info, Player *&player, Player_Mode &player_mode);
    void Run() override;
    void Draw() override;
    json to_json() const override;
    void from_json(const json &j) override;
    ~HardMap();

private:
    void Spawn_Platform();
    void Check_Player_Platform();
    void Spawn_Fire_Block();
    void Delete_Fire_Block();
};