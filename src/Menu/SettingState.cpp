#include "Menu/SettingState.h"
#include "raylib.h"
#include "Menu/SoundManager.h"

SettingState::SettingState() 
    : backButton(80, 80, 40, CircleButton::BACK)
{
    SettingTexture = &MenuImages::GetInstance().SettingTexture;
    
    // Tính toán vị trí để căn giữa SettingTexture
    
    // Tạo các slider cho volume
    float sliderStartY =  300; // Vị trí Y bắt đầu của slider
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
    DrawTexture(*SettingTexture, -bgX, 0, WHITE);
    DrawTexture(*SettingTexture, -bgX + SettingTexture->width, 0, WHITE);

    
    // Vẽ title
    std::string titleText = "SETTINGS";
    int font_scale = 6.0f;
    int size_title = (int)(titleText.size() * 8 * font_scale + 1.0f);
    int titleX = (Screen_w - size_title) / 2;
    int titleY = 100;
    Font_Sprite::DrawText(titleText, titleX, titleY, WHITE, font_scale);
    
    // Vẽ back button
    backButton.Draw();
    
    // Vẽ volume sliders
    musicVolumeSlider->Draw();
    soundVolumeSlider->Draw();
    if (bgX >= SettingTexture->width)
        bgX -= SettingTexture->width;
}

int SettingState::Update() {
    //update background
    float deltaTime = GetFrameTime();
    bgX += scrollSpeed * deltaTime;
    Texture2D background = MenuImages::GetInstance().menuTexture;
    // Reset bgX if it scrolls past the image width




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