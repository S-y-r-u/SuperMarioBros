#pragma once
#include "raylib.h"
#include "sprite.h"
#include "Menu/CursorManager.h"
#include <string>

// Base class Button (interface)
class Button {
public:
    Button(const std::string& text, float x, float y);
    virtual ~Button();

    virtual void Draw() = 0;            
    virtual bool Update() = 0;  // Returns true if clicked (released inside)

protected:
    std::string label;          // Text hiển thị trên button
    float posX, posY;           // Vị trí button
    
    Color normalTextColor = WHITE;
    Color hoverTextColor =  {224, 224, 224, 255};
    
    bool hovered = false;       // Trạng thái hover
    bool pressed = false;       // Trạng thái pressed
};

// Rectangular Button
class RecButton : public Button {
public:
    RecButton(const std::string& text, float x, float y, float width = 303, float height = 100);
    ~RecButton();

    void Draw() override;
    bool Update() override;

private:
    Rectangle bounds;           // Vùng clickable và vẽ của button rectangular
};

// Circle Button
class CircleButton : public Button {
public:
    enum ButtonType {
        NORMAL,     // Button thường (chỉ text)
        PLUS,       // Nút +
        MINUS,      // Nút -
        BACK,        // Nút back (mũi tên)
        PAUSE,       // Nút pause
        YES,        // Nút yes
        NO          // Nút no
    };

    CircleButton(const std::string& text, float x, float y, float r = 50);
    CircleButton(float x, float y, float r = 50.0f);
    CircleButton(float x, float y, float r, ButtonType type);
    ~CircleButton();

    void Draw() override;
    bool Update() override;

private:
    Vector2 center;             // Tâm của button tròn
    float radius;               // Bán kính
    ButtonType buttonType;      // Loại button
    
    bool IsPointInCircle(Vector2 point, Vector2 cent, float r);
};
