#include "Menu/SettingState.h"
#include "raylib.h"
#include "Menu/SoundManager.h"

SettingState::SettingState() 
    : backButton(80, 80, 40, CircleButton::BACK)
{
    MenuTexture = &MenuImages::GetInstance().menuTexture;
    SettingTexture = &MenuImages::GetInstance().SettingTexture;
    
    // Tính toán vị trí để căn giữa SettingTexture
    settingX = (Screen_w - SettingTexture->width) / 2.0f;
    settingY = (Screen_h - SettingTexture->height) / 2.0f ;
    
    // Tạo các slider cho volume
    float sliderStartY = settingY + 200; // Vị trí Y bắt đầu của slider
    float sliderCenterX = Screen_w / 2.0f - 100; // Căn giữa slider
    
    musicVolumeSlider = new MusicButton("Music Volume", sliderCenterX - 15.f, sliderStartY, 200, 20);
    soundVolumeSlider = new MusicButton("Sound Volume", sliderCenterX - 15.f, sliderStartY + 80, 200, 20);

    // Set volume ban đầu từ SoundManager
    musicVolumeSlider->SetVolume(SoundManager::GetInstance().GetMusicVolume());
    soundVolumeSlider->SetVolume(SoundManager::GetInstance().GetSFXVolume());
}

SettingState::~SettingState() {
    delete musicVolumeSlider;
    delete soundVolumeSlider;
}

void SettingState::Draw() {
    // Vẽ background menu
    DrawTexture(*MenuTexture, 0, 0, WHITE);
    
    // Vẽ setting overlay
    if (SettingTexture->id > 0) {
        DrawTexture(*SettingTexture, settingX, settingY, WHITE);
    }
    
    // Vẽ title
    const char* titleText = "SETTINGS";
    int fontSize = 40;
    int textWidth = MeasureText(titleText, fontSize);
    int titleX = (Screen_w - textWidth) / 2;
    int titleY = settingY + 100;
    DrawText(titleText, titleX, titleY, fontSize, BLACK);
    
    // Vẽ back button
    backButton.Draw();
    
    // Vẽ volume sliders
    musicVolumeSlider->Draw();
    soundVolumeSlider->Draw();
    
        // Vẽ instructions - 3 dòng thay vì 2 dòng
    const char* instruction1 = "Use sliders to drag volume control";
    const char* instruction2 = "Use +/- buttons for precise adjustment";
    const char* instruction3 = "Click Back button to return to menu";
    
    int instFontSize = 16;
    int lineSpacing = 20; // Khoảng cách giữa các dòng
    int startY = settingY + 350;
    
    // Căn giữa từng dòng
    int inst1Width = MeasureText(instruction1, instFontSize);
    int inst2Width = MeasureText(instruction2, instFontSize);
    int inst3Width = MeasureText(instruction3, instFontSize);
    
    DrawText(instruction1, (Screen_w - inst1Width) / 2, startY, instFontSize, DARKGRAY);
    DrawText(instruction2, (Screen_w - inst2Width) / 2, startY + lineSpacing, instFontSize, DARKGRAY);
    DrawText(instruction3, (Screen_w - inst3Width) / 2, startY + lineSpacing * 2, instFontSize, DARKGRAY);
}

int SettingState::Update() {
    // Kiểm tra nút back
    if (backButton.Update()) {
        return menuState;  // Quay về menu
    }
    
    // Cập nhật music volume
    if (musicVolumeSlider->Update()) {
        float newVolume = musicVolumeSlider->GetVolume();
        SoundManager::GetInstance().SetMusicVol(newVolume);
    }
    
    // Cập nhật sound volume
    if (soundVolumeSlider->Update()) {
        float newVolume = soundVolumeSlider->GetVolume();
        SoundManager::GetInstance().SetSFXVolume(newVolume);
    }
    
    return settingState;  // Tiếp tục ở setting state
}