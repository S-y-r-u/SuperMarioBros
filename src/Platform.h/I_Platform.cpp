#include "Platform/I_Platform.h"

I_Platform::I_Platform(Vector2 position, Vector2 velocity)
    : animation(nullptr),
      position(position),
      velocity(velocity) {}

void I_Platform::Draw()
{
    Rectangle dest_rec = {position.x, position.y, animation.Get_Current_Rec().width * scale_screen, animation.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(animation.Get_Sprite().sprite, animation.Get_Current_Rec(), dest_rec, Vector2{animation.Get_Current_Rec().width * scale_screen / 2, 0}, 0, WHITE);
}

void I_Platform::Update()
{
    position += velocity * GetFrameTime();
}

Rectangle I_Platform::Get_Bounding_Box() const
{
    return {position.x - animation.Get_Current_Rec().width * scale_screen / 2, position.y, animation.Get_Current_Rec().width * scale_screen, animation.Get_Current_Rec().height * scale_screen};
}

Vector2 I_Platform::Get_Velocity() const
{
    return velocity;
}