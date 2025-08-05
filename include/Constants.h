#pragma once
#include <string>
#include <iostream>

// Screen dimensions
constexpr int Screen_w = 1248;
constexpr int Screen_h = 720;
constexpr float scale_screen = 3.0f;

// Program states
enum ProgramState {
    menuState = 0,
    settingState = 1,
    choosingStageState = 3,
    gameManagerState = 4
};

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

namespace Physics
{
    constexpr float gravity_ = 1000.0f;
}


// Colors (if you want to define custom colors, otherwise use raylib's built-in colors)
// Example:
// #include "raylib.h"
// constexpr Color MARIO_RED = { 228, 53, 36, 255 };

// Asset paths (if you want to centralize them)
// constexpr const char* FONT_PATH = "Assets/Fonts/LilitaOne-Regular.ttf";
// constexpr const char* ICON_PATH = "Assets/Images/mario_icon.png";
