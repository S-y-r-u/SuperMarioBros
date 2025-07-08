#pragma once
#include<string>
#include<iostream>

// Screen dimensions
constexpr int Screen_w = 1000;
constexpr int Screen_h = 600;

// Program states
enum ProgramState {
    menuState = 0,
    settingState = 1,
    gameManagerState = 2
};

constexpr int NUM_MONITORED_KEYS = 16;



// Colors (if you want to define custom colors, otherwise use raylib's built-in colors)
// Example:
// #include "raylib.h"
// constexpr Color MARIO_RED = { 228, 53, 36, 255 };

// Asset paths (if you want to centralize them)
// constexpr const char* FONT_PATH = "Assets/Fonts/LilitaOne-Regular.ttf";
// constexpr const char* ICON_PATH = "Assets/Images/mario_icon.png";
