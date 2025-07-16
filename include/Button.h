#pragma once
#include "raylib.h"
#include <string>

class Button {
public:
    Button(const std::string& text, float x, float y, float width = 200, float height = 60);

    void Draw();
    bool Update();  // Returns true if clicked (released inside)

private:
    Rectangle bounds;
    std::string label;

    Color normalColor = LIGHTGRAY;
    Color hoverColor = GRAY;
    Color textColor = BLACK;

    bool hovered = false;
};