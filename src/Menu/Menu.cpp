#include "Menu/Menu.h"
#include "raylib.h"
#include <cmath>

Menu::Menu() : 
    playButton("PLAY", 350, 400, 200, 50),
    settingBtn("SETTINGS", 640, 400, 200, 50),
    infoButton("INFO", 350, 600, 200, 50),
    quitButton("QUIT", 640, 600, 200, 50),
    mapButton("MAP", 350, 500, 200, 50),
    characterButton("CHARACTER", 640, 500, 200, 50),
    titleBaseY(50.0f),      // Vị trí Y cơ bản của title
    titleAnimTime(0.0f),     // Thời gian animation
    titleAnimSpeed(2.0f),    // Tốc độ animation (càng lớn càng nhanh)
    titleAnimRange(15.0f)    // Phạm vi chuyển động (±15 pixels)
{
    MenuTexture = &MenuImages::GetInstance().menuTexture;
    MenuTitleTexture = &MenuImages::GetInstance().MenuTitleTexture;
    titleY = titleBaseY;
}

void Menu::Draw() {
    // Vẽ background
    DrawTexture(*MenuTexture, 0, 0, WHITE);
    
    // Vẽ title với animation
    if (MenuTitleTexture->id > 0) {
        float titleX = (Screen_w - MenuTitleTexture->width) / 2.0f - 10.0f; // Căn giữa
        DrawTexture(*MenuTitleTexture, titleX, titleY, WHITE);
    }
    
    // Vẽ các button
    playButton.Draw();
    settingBtn.Draw();
    infoButton.Draw();
    quitButton.Draw();
    mapButton.Draw();
    characterButton.Draw();
}

int Menu::Update() {
    // Cập nhật animation cho title
    titleAnimTime += GetFrameTime();
    titleY = titleBaseY + sin(titleAnimTime * titleAnimSpeed) * titleAnimRange;
    
    // Xử lý button clicks
    if (playButton.Update()) {
        std::cout << "PLAY\n";
        return gameManagerState; // Trở về game manager state
    }
    if (settingBtn.Update()) {
        return settingState;
    }
    if (infoButton.Update()) {
        // return infoState;
    }
    if (quitButton.Update()) {
        // return quitState;
    }
    if (mapButton.Update()) {
        return choosingStageState;
    }
    if (characterButton.Update()) {
        return choosingCharacterState;
    }
    return menuState;
}

Menu::~Menu() {
    // Destructor
}

// Static instance
MenuImages& MenuImages::GetInstance() {
    static MenuImages instance;
    return instance;
}

void MenuImages::Load() {
    menuTexture = LoadTexture("Menu/Menu.png");
    buttonTexture = LoadTexture("Menu/Button.png");
    MenuTitleTexture = LoadTexture("Menu/SuperMarioTitle.png");
    buttonBackTexture = LoadTexture("Menu/Back.png");
    buttonPlusTexture = LoadTexture("Menu/Plus.png");
    buttonMinusTexture = LoadTexture("Menu/Minus.png");
    SettingTexture = LoadTexture("Menu/Setting.jpg");
    MarioIcon = LoadTexture("Menu/MarioIcon.png");

    // Set rectangles
    menu_background = {0, 0, (float)menuTexture.width, (float)menuTexture.height};
    button_normal = {0, 0, (float)buttonTexture.width, (float)buttonTexture.height};
    menu_title = {0, 0, (float)MenuTitleTexture.width, (float)MenuTitleTexture.height};
    button_plus = {0, 0, (float)buttonPlusTexture.width, (float)buttonPlusTexture.height};
    button_minus = {0, 0, (float)buttonMinusTexture.width, (float)buttonMinusTexture.height};
    button_back = {0, 0, (float)buttonBackTexture.width, (float)buttonBackTexture.height};
    setting_texture = {0, 0, (float)SettingTexture.width, (float)SettingTexture.height};
    mario_icon = {0, 0, (float)MarioIcon.width, (float)MarioIcon.height};
}

void MenuImages::Unload() {
    if (menuTexture.id > 0) {
        UnloadTexture(menuTexture);
        menuTexture.id = 0;
    }
    if (buttonTexture.id > 0) {
        UnloadTexture(buttonTexture);
        buttonTexture.id = 0;
    }
    if (MenuTitleTexture.id > 0) {
        UnloadTexture(MenuTitleTexture);
        MenuTitleTexture.id = 0;
    }
    if (buttonBackTexture.id > 0) {
        UnloadTexture(buttonBackTexture);
        buttonBackTexture.id = 0;
    }
    if (buttonPlusTexture.id > 0) {
        UnloadTexture(buttonPlusTexture);
        buttonPlusTexture.id = 0;
    }
    if (buttonMinusTexture.id > 0) {
        UnloadTexture(buttonMinusTexture);
        buttonMinusTexture.id = 0;
    }
}