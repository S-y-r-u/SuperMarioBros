#include "Button.h"
#include <iostream>

Button::Button(const std::string& text, float x, float y, float width, float height) {
    label = text;
    bounds = {x, y, width, height};
}

void Button::Draw() {
    // Define colors for button and shadow
    Color fillColor = hovered ? Color{255, 228, 100, 255} : YELLOW;
    Color shadowColor = Color{0, 0, 0, 60};
    int cornerRadius = 10;

    // Draw shadow (offset by 3px)
    DrawRectangleRounded({bounds.x + 3, bounds.y + 3, bounds.width, bounds.height}, 0.5f, cornerRadius, shadowColor);

    // Draw rounded button
    DrawRectangleRounded(bounds, 0.5f, cornerRadius, fillColor);

    // Draw centered text
    int fontSize = 20;
    int textWidth = MeasureText(label.c_str(), fontSize);
    DrawText(label.c_str(), bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - fontSize) / 2, fontSize, BLACK);
}

bool Button::Update() {
    // Check mouse hover state
    Vector2 mouse = GetMousePosition();
    hovered = CheckCollisionPointRec(mouse, bounds);

    // Return true if button is clicked (left mouse button released)
    return hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}