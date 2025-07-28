#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Menu/Button.h"
#include "Menu/MusicButton.h"
#include "Menu/Menu.h"

class SettingState {
public:
    SettingState();
    void Draw();
    int Update();
    ~SettingState();
    
private:
    Texture* MenuTexture;           // Background menu
    Texture* SettingTexture;        // Setting overlay texture
    
    CircleButton backButton;        // Nút back để quay về menu
    MusicButton* musicVolumeSlider; // Slider điều chỉnh nhạc
    MusicButton* soundVolumeSlider; // Slider điều chỉnh sound effects
    
    // Vị trí để vẽ SettingTexture
    float settingX;
    float settingY;
};