#include "Menu/Button.h"
#include "Menu/Menu.h"
#include <cmath>

// Base Button class
Button::Button(const std::string &text, float x, float y)
    : label(text), posX(x), posY(y)
{
}

Button::~Button()
{
}

// RecButton implementation
RecButton::RecButton(const std::string &text, float x, float y, float width, float height)
    : Button(text, x, y), bounds{x, y, width, height}
{
}

RecButton::~RecButton()
{
}

void RecButton::Draw()
{
    MenuImages &menuImg = MenuImages::GetInstance();
    Color tint = hovered ? Color{200, 200, 200, 255} : WHITE;

    // Vẽ nền button
    DrawTexturePro(menuImg.buttonTexture,
                   menuImg.button_normal,
                   bounds,
                   Vector2{0, 0},
                   0.0f,
                   tint);

    // Tính kích thước text
    float scale = hovered ? 2.8f : 2.5f;
    float charWidth = 8.0f * scale + 1.0f; // mỗi ký tự có 1 khoảng cách 1px
    float charHeight = 8.0f * scale + 1.0f;

    float textWidth = label.size() * charWidth;
    float textHeight = charHeight;

    // Căn giữa trong bounds
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - textHeight) / 2.0f;

    // Vẽ text
    Color textColor = hovered ? hoverTextColor : normalTextColor;
    Font_Sprite::DrawText(label, textX, textY, textColor, scale);
}

bool RecButton::Update()
{
    Vector2 mousePos = GetMousePosition();
    hovered = CheckCollisionPointRec(mousePos, bounds);
    if (hovered)
        CursorManager::Set_Cursor(MOUSE_CURSOR_POINTING_HAND);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        pressed = true;
    }

    if (pressed && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && hovered)
    {
        pressed = false;
        return true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        pressed = false;
    }

    return false;
}

// CircleButton implementation
CircleButton::CircleButton(const std::string &text, float x, float y, float r)
    : Button(text, x, y), center{x, y}, radius(r), buttonType(NORMAL)
{
}

CircleButton::CircleButton(float x, float y, float r)
    : Button("", x, y), center{x, y}, radius(r), buttonType(NORMAL)
{
}

CircleButton::CircleButton(float x, float y, float r, ButtonType type)
    : Button("", x, y), center{x, y}, radius(r), buttonType(type)
{
}

CircleButton::~CircleButton()
{
}

bool CircleButton::IsPointInCircle(Vector2 point, Vector2 cent, float r)
{
    float dx = point.x - cent.x;
    float dy = point.y - cent.y;
    return (dx * dx + dy * dy) <= (r * r);
}

void CircleButton::Draw()
{
    MenuImages &menuImg = MenuImages::GetInstance();
    Color tint = hovered ? Color{200, 200, 200, 255} : WHITE;
    Rectangle destRect = {center.x - radius, center.y - radius, radius * 2, radius * 2};

    // Vẽ texture tương ứng với buttonType
    switch (buttonType)
    {
    case PLUS:
        DrawTexturePro(menuImg.buttonPlusTexture, menuImg.button_plus, destRect, Vector2{0, 0}, 0.0f, tint);
        break;

    case MINUS:
        DrawTexturePro(menuImg.buttonMinusTexture, menuImg.button_minus, destRect, Vector2{0, 0}, 0.0f, tint);
        break;

    case BACK:
        DrawTexturePro(menuImg.buttonBackTexture, menuImg.button_back, destRect, Vector2{0, 0}, 0.0f, tint);
        break;

    case NORMAL:
    default:
        // NORMAL chỉ vẽ text, không có background
        if (!label.empty())
        {
            int fontSize = hovered ? 22 : 18;
            Font font = GetFontDefault();
            Vector2 textSize = MeasureTextEx(font, label.c_str(), fontSize, 1.0f);

            Vector2 textPos = {
                center.x - textSize.x / 2,
                center.y - textSize.y / 2};

            if (hovered)
            {
                Vector2 shadowPos = {textPos.x + 1, textPos.y + 1};
                DrawTextEx(font, label.c_str(), shadowPos, fontSize, 1.0f, Color{50, 50, 50, 100});
            }

            DrawTextEx(font, label.c_str(), textPos, fontSize, 1.0f, normalTextColor);
        }
        break;
    }
}

bool CircleButton::Update()
{
    Vector2 mousePos = GetMousePosition();
    hovered = IsPointInCircle(mousePos, center, radius);
    if (hovered)
        CursorManager::Set_Cursor(MOUSE_CURSOR_POINTING_HAND);

    if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        pressed = true;
    }

    if (pressed && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && hovered)
    {
        pressed = false;
        return true;
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        pressed = false;
    }

    return false;
}