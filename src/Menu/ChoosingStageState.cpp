#include "Menu/ChoosingStageState.h"
#include "raylib.h"

ChoosingStageState::ChoosingStageState()
    : selectedDifficulty(Difficulty::Easy),
      backButton(80, 80, 40, CircleButton::BACK)// Nút back tròn ở góc trái       
{
    MenuTexture = &MenuImages::GetInstance().menuTexture;

    // Create buttons arranged horizontally
    float buttonWidth = 150;
    float buttonHeight = 50;
    float spacing = 50;
    float totalWidth = 3 * buttonWidth + 2 * spacing;
    float startX = (Screen_w - totalWidth) / 2;
    float buttonY = 550;

    easyButton = new RecButton("EASY", startX, buttonY, buttonWidth, buttonHeight);
    mediumButton = new RecButton("MEDIUM", startX + buttonWidth + spacing, buttonY, buttonWidth, buttonHeight);
    hardButton = new RecButton("HARD", startX + 2 * (buttonWidth + spacing), buttonY, buttonWidth, buttonHeight);
}

ChoosingStageState::~ChoosingStageState()
{
    delete easyButton;
    delete mediumButton;
    delete hardButton;
    // Không cần UnloadTexture vì MenuImages quản lý
}

void ChoosingStageState::Draw()
{
    DrawTexture(*MenuTexture, 0, 0, WHITE);

    // Center the title text
    std::string titleText = "Choose Difficulty";
    float font_scale = 6.0f;
    int text_width = (int)(titleText.size() * 8 * font_scale + 1.0f);
    int titleX = (Screen_w - text_width) / 2;
    Font_Sprite::DrawText(titleText, titleX, 80, WHITE, font_scale);

    // Draw back button
    backButton.Draw();


    // Draw difficulty buttons
    easyButton->Draw();
    mediumButton->Draw();
    hardButton->Draw();
}

int ChoosingStageState::Update()
{
    // Kiểm tra nút back
    if (backButton.Update())
    {
        return menuState; // Quay về menu
    }

    // Kiểm tra các nút difficulty
    if (easyButton->Update())
    {
        selectedDifficulty = Difficulty::Easy;
        return menuState;
    }
    if (mediumButton->Update())
    {
        selectedDifficulty = Difficulty::Medium;
        return menuState;
    }
    if (hardButton->Update())
    {
        selectedDifficulty = Difficulty::Hard;
        return menuState;
    }

    return choosingStageState;
}

Difficulty ChoosingStageState::GetSelectedDifficulty() const
{
    return selectedDifficulty;
}