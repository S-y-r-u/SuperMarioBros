#include "ChoosingStageState.h"
#include "raylib.h"

ChoosingStageState::ChoosingStageState() :selectedDifficulty(Difficulty::Easy){
    MenuTexture = LoadTexture("Menu/Menu.jpg");
    
    // Create buttons arranged horizontally
    float buttonWidth = 150;
    float buttonHeight = 50;
    float spacing = 50;
    float totalWidth = 3 * buttonWidth + 2 * spacing;
    float startX = (Screen_w - totalWidth) / 2;
    float buttonY = 550;
    
    easyButton = new Button("EASY", startX, buttonY, buttonWidth, buttonHeight);
    mediumButton = new Button("MEDIUM", startX + buttonWidth + spacing, buttonY, buttonWidth, buttonHeight);
    hardButton = new Button("HARD", startX + 2 * (buttonWidth + spacing), buttonY, buttonWidth, buttonHeight);
}

ChoosingStageState::~ChoosingStageState() {
    delete easyButton;
    delete mediumButton;
    delete hardButton;
    UnloadTexture(MenuTexture);
}

void ChoosingStageState::Draw() {
    DrawTexture(MenuTexture, 0, 0, WHITE);
    
    // Center the title text
    const char* titleText = "Choose Difficulty";
    int textWidth = MeasureText(titleText, 50);
    int titleX = (Screen_w - textWidth) / 2;
    DrawText(titleText, titleX, 50, 50, BLACK);
    
    // Draw buttons
    easyButton->Draw();
    mediumButton->Draw();
    hardButton->Draw();
}

int ChoosingStageState::Update() {
    if (easyButton->Update()) {
        selectedDifficulty = Difficulty::Easy;
        return gameManagerState;
    }
    if (mediumButton->Update()) {
        selectedDifficulty = Difficulty::Medium;
        return gameManagerState;
    }
    if (hardButton->Update()) {
        selectedDifficulty = Difficulty::Hard;
        return gameManagerState;
    }
    return choosingStageState;
}

Difficulty ChoosingStageState::GetSelectedDifficulty() const {
    return selectedDifficulty;
}
