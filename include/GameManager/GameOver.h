#pragma once
#include "raylib.h"
#include "sprite.h"
#include "PlayerInformation.h"
#include "Constants.h"

class GameOver
{
private:
    PlayerInformation* player_info;
    float timer_;
    const float time_to_show = 4.0f; // Thời gian hiển thị Game Over
public:
    GameOver();
    void SetPlayerInformation(PlayerInformation *info);
    void Draw() const;
    int Update();
};
