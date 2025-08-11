#pragma once
#include "sprite.h"
#include "raylib.h"
#include "GameManager/Animation.h"

class Flag
{
private:
    Vector2 pos_;
    Vector2 velocity_;

protected:
    Animation animation_;

public:
    Flag(Vector2 pos);
    virtual void Update(float deltaTime) = 0;
    void Draw();
    void Set_Pos(Vector2 pos);
    Vector2 Get_Pos() const;
    void Set_Velocity(Vector2 vel);
    void Update_Pos();
};