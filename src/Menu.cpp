#include "Menu.h"



void Menu::Init() {
    // Load resources if needed
}

void Menu::Draw() {
    DrawText("MARIO GAME", 420, 150, 32, DARKBLUE);
    DrawRectangleRec(playBtn, LIGHTGRAY);
    DrawText("PLAY", 480, 265, 24, BLACK);
    DrawRectangleRec(settingBtn, LIGHTGRAY);
    DrawText("SETTING", 460, 365, 24, BLACK);
}

int Menu::HandleEvent() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, playBtn)) {
            return gameManagerState;
        }
        if (CheckCollisionPointRec(mouse, settingBtn)) {
            return settingState;
        }
    }
    return menuState;
}

Menu::~Menu() {
    // Unload resources if needed
}
