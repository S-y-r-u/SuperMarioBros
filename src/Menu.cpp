#include "Menu.h"
#include "raylib.h"

Rectangle playBtn = { 400, 250, 200, 60 };
Rectangle settingBtn = { 400, 350, 200, 60 };

Menu::Menu() {
	// Constructor can be used to initialize any member variables if needed
}

void Menu::Init() {}

void Menu::Draw() {
    DrawText("MARIO GAME", 420, 150, 32, DARKBLUE);
    DrawRectangleRec(playBtn, LIGHTGRAY);
    DrawText("PLAY", 480, 265, 24, BLACK);
    DrawRectangleRec(settingBtn, LIGHTGRAY);
    DrawText("SETTING", 460, 365, 24, BLACK);
}

int Menu::Update() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, playBtn)) {
            return choosingStageState;
        }
        if (CheckCollisionPointRec(mouse, settingBtn)) {
            return settingState;
        }
    }
    return menuState;
}

Menu::~Menu() {}
