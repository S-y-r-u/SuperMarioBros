#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Menu/Button.h"

class Menu {
private:
    RecButton playButton;
    RecButton settingBtn;
    RecButton infoButton;
    RecButton quitButton;
    Texture* MenuTexture;
    Texture* MenuTitleTexture;
    
    // Animation variables cho title
    float titleY;
    float titleBaseY;
    float titleAnimTime;
    float titleAnimSpeed;
    float titleAnimRange;
    
public:
    Menu();
    void Draw();
    int Update();
    ~Menu();
};

// Menu Images struct
struct MenuImages
{
    Texture2D menuTexture;
    Texture2D buttonTexture;
    Texture2D MenuTitleTexture;
    Texture2D buttonBackTexture;
    Texture2D buttonPlusTexture;
    Texture2D buttonMinusTexture;
    Texture2D SettingTexture;

    Rectangle menu_title;
    Rectangle menu_background;
    Rectangle button_normal;
    Rectangle button_plus;
    Rectangle button_minus;
    Rectangle button_back;
    Rectangle setting_texture;

    void Load();
    void Unload();
    
    static MenuImages& GetInstance();
    
private:
    MenuImages() = default;
};