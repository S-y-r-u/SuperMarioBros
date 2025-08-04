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
    Texture* SettingTexture;           // Background menu
    
    CircleButton backButton;        // Nút back để quay về menu
    MusicButton* musicVolumeSlider; // Slider điều chỉnh nhạc
    MusicButton* soundVolumeSlider; // Slider điều chỉnh sound effects
    
    float bgX = 0.0f;
    float scrollSpeed = 50.0f; // pixels per second

};