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

json I_Platform::to_json() const {
    json j;
    j["position"] = {position.x, position.y};
    j["velocity"] = {velocity.x, velocity.y};
    // Note: You might want to serialize the animation state as well if needed
    return j;
}

void I_Platform::from_json(const json &j) {
    position.x = j.at("position")[0];
    position.y = j.at("position")[1];
    velocity.x = j.at("velocity")[0];
    velocity.y = j.at("velocity")[1];
    // Note: You might want to deserialize the animation state as well if needed
}
