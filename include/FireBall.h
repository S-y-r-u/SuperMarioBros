#pragma once
#include "sprite.h"
#include "Constants.h"

enum class FireBallState {Fly, Explode};

class FireBall{
    private:
        Vector2 position;
        Vector2 velocity;
        bool isActive;
        FireBallState state;
        
        int currentFrame;
        float frameTimer;
        float animationSpeed;
        SpriteSheet* texture = nullptr;

    public:
        FireBall(Vector2 pos, bool facingLeft);
        ~FireBall();

        bool getActive() const;
        std :: vector<Rectangle> getFireBallFrame() const;
        void update(float dt);    
        void explode();
        void draw();
};