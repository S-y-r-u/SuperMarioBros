#include "Menu/ChoosingCharacter.h"
#include "raylib.h"
#include "sprite.h"

ChoosingCharacter::ChoosingCharacter()
    : backButton(80, 80, 40, CircleButton::BACK) // Nút back tròn ở góc trái
{
    MenuTexture = &MenuImages::GetInstance().menuTexture;

    // Create buttons arranged horizontally
    float buttonWidth = 150;
    float buttonHeight = 50;

    marioButton = new RecButton("MARIO", 145, 660, buttonWidth, buttonHeight);
    multiplayerButton = new RecButton("2PLAYERS", 500, 660, buttonWidth + 30, buttonHeight);
    luigiButton = new RecButton("LUIGI", 930, 660, buttonWidth, buttonHeight);
}

ChoosingCharacter::~ChoosingCharacter()
{
    delete marioButton;
    delete luigiButton;
    delete multiplayerButton;
    // Không cần UnloadTexture vì MenuImages quản lý
}

void ChoosingCharacter::Draw()
{
    DrawTexture(*MenuTexture, 0, 0, WHITE);

    // Center the title text
    std::string titleText = "Choose Character";
    float font_scale = 6.0f;
    int text_width = (int)(titleText.size() * 8 * font_scale + 1.0f);
    int titleX = (Screen_w - text_width) / 2;
    Font_Sprite::DrawText(titleText, titleX, 80, WHITE, font_scale);

    // Draw back button
    backButton.Draw();

    // Draw character buttons
    marioButton->Draw();
    luigiButton->Draw();
    multiplayerButton->Draw();

    if (selectedCharacter == Player_Mode::MARIO_PLAYER)
    {
        Rectangle arrow = {80, 660, Screen_Sprite::arrow_.width * 5.0f, Screen_Sprite::arrow_.height * 5.0f};
        DrawTexturePro(Screen_Sprite::screen_.sprite, Screen_Sprite::arrow_, arrow, {0, 0}, 0.0f, WHITE);
    }
    else if (selectedCharacter == Player_Mode::LUIGI_PLAYER)
    {
        Rectangle arrow = {865, 660, Screen_Sprite::arrow_.width * 5.0f, Screen_Sprite::arrow_.height * 5.0f};
        DrawTexturePro(Screen_Sprite::screen_.sprite, Screen_Sprite::arrow_, arrow, {0, 0}, 0.0f, WHITE);
    }
    else if (selectedCharacter == Player_Mode::MULTI_PLAYER)
    {
        Rectangle arrow = {435, 660, Screen_Sprite::arrow_.width * 5.0f, Screen_Sprite::arrow_.height * 5.0f};
        DrawTexturePro(Screen_Sprite::screen_.sprite, Screen_Sprite::arrow_, arrow, {0, 0}, 0.0f, WHITE);
    }
}

int ChoosingCharacter::Update()
{
    // Kiểm tra nút back
    if (backButton.Update())
    {
        return menuState; // Quay về menu
    }

    // Kiểm tra các nút character
    if (marioButton->Update())
    {
        selectedCharacter = Player_Mode::MARIO_PLAYER;
    }
    if (luigiButton->Update())
    {
        selectedCharacter = Player_Mode::LUIGI_PLAYER;
    }
    if (multiplayerButton->Update())
    {
        selectedCharacter = Player_Mode::MULTI_PLAYER;
    }

    return choosingCharacterState;
}

Player_Mode ChoosingCharacter::GetCharacter() const
{
    return selectedCharacter;
}