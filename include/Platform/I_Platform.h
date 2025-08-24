#pragma once
#include "GameManager/Animation.h"
#include "Constants.h"
#include "sprite.h"
#include <raylib.h>
#include <raymath.h>

class I_Platform
{
protected:
    Animation animation;
private:
    Vector2 position;
    Vector2 velocity;
public:
    I_Platform(Vector2 position, Vector2 velocity);
    virtual ~I_Platform() = default;
    void Draw();
    void Update();
    Rectangle Get_Bounding_Box() const;
    Vector2 Get_Velocity() const;
    json to_json() const;
    void from_json(const json &j);
};  