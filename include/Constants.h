#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

// Screen dimensions
constexpr int Screen_w = 1248;
constexpr int Screen_h = 720;
constexpr float scale_screen = 3.0f;
constexpr float Tile_Size = 48.0f;

// Program states
enum ProgramState
{
    menuState = 0,
    settingState = 1,
    choosingStageState = 2,
    choosingCharacterState = 3,
    gameManagerState = 4,
    gameOverState = 5,
    timeUpState = 6,
    continueState = 7
};

enum class Player_Mode
{
    MARIO_PLAYER,
    LUIGI_PLAYER,
    MULTI_PLAYER
};

enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

namespace Physics
{
    constexpr float gravity_ = 1000.0f;
}

enum class EnemyType
{
    Goomba,
    KoopaTroopaWalking,
    KoopaTroopaFlying,
    Latiku,
    PiranhaPlant,
    BomberBill,
    Spiny
};