#include "Menu/MusicButton.h"
#include "Menu/Menu.h"
#include "raylib.h"
#include <algorithm>
#include <cstdio>

// MusicButton implementation
MusicButton::MusicButton(const std::string &text, float x, float y, float sliderW, float sliderH)
    : Button(text, x, y), sliderWidth(sliderW), sliderHeight(sliderH),
      volume(0.5f), isDragging(false), knobRadius(sliderHeight / 2 + 5)
{

    // Thiết lập slider track
    sliderTrack = {x, y, sliderWidth, sliderHeight};

    // Thiết lập knob position ban đầu
    UpdateKnobPosition();

    // Tạo nút + và -
    float buttonY = y + sliderHeight / 2;
    float buttonRadius = 15.0f;

    minusButton = new CircleButton(x - 20, buttonY, buttonRadius, CircleButton::MINUS);
    plusButton = new CircleButton(x + sliderWidth + 20, buttonY, buttonRadius, CircleButton::PLUS);
}

MusicButton::~MusicButton()
{
    delete plusButton;
    delete minusButton;
}

void MusicButton::SetVolume(float vol)
{
    volume = std::max(0.0f, std::min(1.0f, vol));
    UpdateKnobPosition();
}

void MusicButton::UpdateKnobPosition()
{
    float knobX = sliderTrack.x + (volume * (sliderTrack.width - knobRadius * 2)) + knobRadius;
    float knobY = sliderTrack.y + sliderTrack.height / 2;
    sliderKnob = {knobX - knobRadius, knobY - knobRadius, knobRadius * 2, knobRadius * 2};
}

void MusicButton::UpdateVolumeFromKnob()
{
    float knobCenterX = sliderKnob.x + sliderKnob.width / 2;
    float relativePos = (knobCenterX - sliderTrack.x - knobRadius) / (sliderTrack.width - knobRadius * 2);
    volume = std::max(0.0f, std::min(1.0f, relativePos));
}

bool MusicButton::IsPointInKnob(Vector2 point)
{
    Vector2 knobCenter = {sliderKnob.x + sliderKnob.width / 2, sliderKnob.y + sliderKnob.height / 2};
    float dx = point.x - knobCenter.x;
    float dy = point.y - knobCenter.y;
    return (dx * dx + dy * dy) <= (knobRadius * knobRadius);
}

void MusicButton::Draw()
{
    MenuImages &menuImg = MenuImages::GetInstance();

    // Vẽ label
    if (!label.empty())
    {
        float font_scale = 2.0f;
        Font_Sprite::DrawText(label, posX, posY - (8 * font_scale * 1.4f), WHITE, font_scale);
    }

    // Vẽ slider track (thanh dài)
    DrawRectangleRec(sliderTrack, LIGHTGRAY);
    DrawRectangleLinesEx(sliderTrack, 2, DARKGRAY);

    // Vẽ phần đã fill (màu xanh)
    Rectangle filledTrack = {
        sliderTrack.x,
        sliderTrack.y,
        volume * sliderTrack.width,
        sliderTrack.height};
    DrawRectangleRec(filledTrack, BLUE);

    // Vẽ knob (hình tròn)
    Color knobColor = (hovered || isDragging) ? GRAY : WHITE;
    DrawRectangleRec(sliderKnob, knobColor);
    DrawRectangleLinesEx(sliderKnob, 2, DARKGRAY);

    // Vẽ volume percentage
    // Tạo chuỗi volume dạng "50%"
    int vol_int = static_cast<int>(volume * 100);
    std::string volumeText = std::to_string(vol_int) + "%";

    // Tính toạ độ (giữ nguyên hoặc căn giữa nếu muốn)
    Vector2 volumeTextPos = {
        posX + sliderWidth + 40,
        posY + sliderHeight / 2 - 8};

    // Dùng hệ thống sprite font để vẽ
    Font_Sprite::DrawText(volumeText, volumeTextPos.x, volumeTextPos.y, WHITE, 2.0f);

    // Vẽ nút + và -
    minusButton->Draw();
    plusButton->Draw();
}

bool MusicButton::Update()
{
    Vector2 mousePos = GetMousePosition();
    bool valueChanged = false;

    // Xử lý nút + và -
    if (plusButton->Update())
    {
        SetVolume(volume + 0.1f);
        valueChanged = true;
    }
    if (minusButton->Update())
    {
        SetVolume(volume - 0.1f);
        valueChanged = true;
    }

    // Xử lý slider
    hovered = IsPointInKnob(mousePos);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsPointInKnob(mousePos))
    {
        isDragging = true;
        pressed = true;
    }

    if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        // Cập nhật vị trí knob theo mouse
        float newKnobX = std::max(sliderTrack.x + knobRadius,
                                  std::min(mousePos.x, sliderTrack.x + sliderTrack.width - knobRadius));
        sliderKnob.x = newKnobX - knobRadius;
        UpdateVolumeFromKnob();
        valueChanged = true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (isDragging)
        {
            isDragging = false;
            pressed = false;
            valueChanged = true;
        }
    }

    return valueChanged;
}