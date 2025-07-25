#pragma once 
#include "Constants.h"
#include "Sprite.h"

constexpr float Tile_Size = 16.0f * scale_screen;

class Enemy
{
protected:
    SpriteSheet sprite_;
    Vector2 position_;
    Vector2 velocity_;
    Rectangle rec_;
    float gravity_;

    int frame_;
    bool isGround_;
public:
    Enemy(Vector2 startPos , Vector2 velocity, float gravity);

    virtual ~Enemy() = default;

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;

    Rectangle Get_Draw_Rec() const;
    Vector2 Get_Pos() const;
    
    
    virtual void Notify_Fall(float deltaTime);
    virtual void Notify_On_Ground();
    virtual void Notify_Change_Direct();
};