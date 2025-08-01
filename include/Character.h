#pragma once
#include "raylib.h"
#include "Constants.h"
#include "sprite.h"

class Character{
    protected: 
        Vector2 position;
        Vector2 velocity;
        bool isGround;
        bool isFacingLeft;
        float speed;
        float gravity;
        SpriteSheet* texture = nullptr;

    public:
        Character(Vector2 startPos);
        virtual ~Character();

        Vector2 getPosition() const;
        void Set_Pos(Vector2 newPos) { position = newPos; }
        virtual Rectangle get_draw_rec() = 0;
        virtual Rectangle Get_Previous_Rec() = 0;
        virtual void MoveRight() = 0;
        virtual void MoveLeft() = 0;  
        virtual void StopMoving() = 0;
        virtual void update(float dt) = 0;
        virtual void draw() = 0; 
           
};