#include "ChoosingStageState.h"
#include "raylib.h"

void ChoosingStageState::Init() {
    selectedDifficulty = Difficulty::Easy;
}

void ChoosingStageState::Draw() {
    DrawText("Choose Difficulty", 400, 150, 32, DARKBLUE);

    DrawRectangle(400, 250, 200, 50, LIGHTGRAY);
    DrawText("EASY", 480, 265, 24, BLACK);

    DrawRectangle(400, 320, 200, 50, LIGHTGRAY);
    DrawText("MEDIUM", 465, 335, 24, BLACK);

    DrawRectangle(400, 390, 200, 50, LIGHTGRAY);
    DrawText("HARD", 480, 405, 24, BLACK);
}

int ChoosingStageState::Update() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, { 400, 250, 200, 50 })) {
            selectedDifficulty = Difficulty::Easy;
            return gameManagerState;
        }
        if (CheckCollisionPointRec(mouse, { 400, 320, 200, 50 })) {
            selectedDifficulty = Difficulty::Medium;
            return gameManagerState;
        }
        if (CheckCollisionPointRec(mouse, { 400, 390, 200, 50 })) {
            selectedDifficulty = Difficulty::Hard;
            return gameManagerState;
        }
    }
    return choosingStageState;
}

Difficulty ChoosingStageState::GetSelectedDifficulty() const {
    return selectedDifficulty;
}
