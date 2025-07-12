#pragma once
#include "raylib.h"

class Character{
    protected: 
        Vector2 position;
        Vector2 velocity;
        bool isFacingLeft = 0;
        float speed;
        Texture2D* texture = nullptr;
    public:
        Character(Vector2 startPos);
        virtual ~Character();
        virtual void handleInput() = 0;  
        virtual void update(float dt) = 0;
        virtual void draw() = 0;    
};