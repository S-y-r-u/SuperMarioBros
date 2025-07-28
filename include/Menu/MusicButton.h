#pragma once
#include "Menu/Button.h"
#include "raylib.h"
#include <algorithm>

// Music Volume Button (slider)
class MusicButton : public Button {
public:
    MusicButton(const std::string& label, float x, float y, float sliderWidth = 200, float sliderHeight = 20);
    ~MusicButton();

    void Draw() override;
    bool Update() override;
    
    // Getter/Setter cho volume
    float GetVolume() const { return volume; }
    void SetVolume(float vol);
    
private:
    float sliderWidth;
    float sliderHeight;
    float volume;               // 0.0f - 1.0f
    
    Rectangle sliderTrack;      // Thanh dài
    Rectangle sliderKnob;       // Hình tròn trượt
    
    CircleButton* plusButton;   // Nút +
    CircleButton* minusButton;  // Nút -
    
    bool isDragging;            // Đang kéo slider
    float knobRadius;
    
    void UpdateKnobPosition();
    void UpdateVolumeFromKnob();
    bool IsPointInKnob(Vector2 point);
};