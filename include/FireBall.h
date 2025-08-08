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
        bool isGround; 

        int currentFrame;
        float frameTimer;
        float animationSpeed;
        SpriteSheet* texture = nullptr;

    public:
        FireBall(Vector2 pos, bool facingLeft);
        ~FireBall();

        bool getActive() const;
        Rectangle get_draw_rec();
        Vector2 getVelocity() const {return velocity;}
        std :: vector<Rectangle> getFireBallFrame() const;
        void setPosition(Vector2 newPos);
        void notifyOnGround();
        void reboundOnSurface();

        void update(float dt, const Camera2D& camera);    
        void explode();
        void draw();
};