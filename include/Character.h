#pragma once
#include "raylib.h"
#include "Constants.h"
#include "sprite.h"

class Character{
    protected: 
        Vector2 position;
        Vector2 velocity;
        bool isFacingLeft = 0;
        float speed = 150.0f;
        float gravity;
        SpriteSheet* texture = nullptr;

    public:
        Character(Vector2 startPos);
        virtual ~Character();

        Vector2 getPosition() const;
        virtual Rectangle get_draw_rec() = 0;
        virtual void MoveRight() = 0;
        virtual void MoveLeft() = 0;  
        virtual void StopMoving() = 0;
        virtual void update(float dt) = 0;
        virtual void draw() = 0; 
           
};