#pragma once
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Player/FireBall.h"
#include "Item/MushRoom.h"
#include "Item/Star.h"
#include "Enemy/KoopaTroopa.h"
#include <vector>
#include <fstream>

class MapManagement
{
private:
    std::vector<std::vector<int>> Map;

public:
    MapManagement() = default;
    MapManagement(const std::string &filename);
    void Check_Player_Vs_Ground(Player &player);
    void Check_Enemy_Vs_Ground(Enemy &enemy);
    void Check_Item_Vs_Ground(Item *item);
    void LoadMapFromFile(const std::string &filename);
    int GetHeight() const;
    int GetWidth() const;
    int GetTile(int x, int y) const;

    json to_json() const;
    void from_json(const json &j);
};