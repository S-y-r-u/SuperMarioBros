#include "FireBall.h"
#include <iostream>

FireBall :: FireBall(Vector2 pos, bool facingLeft){
    position = pos;
    this -> texture = &Item_Sprite::item_;

    isActive = true;
    state = FireBallState :: Fly;
    float speedX = 550.0f, speedY = 20.0f;
    if(facingLeft)  velocity = {-speedX, speedY};
    else velocity = {speedX, speedY};
    isGround = true;

    currentFrame = 0;
    frameTimer = 0.0f;
    animationSpeed = 1.0/12.0;
}

FireBall :: ~FireBall(){

}

bool FireBall :: getActive() const{
    return isActive;
}

void FireBall :: setPosition(Vector2 newPos){
    position = newPos;
}

void FireBall :: notifyOnGround(){
    isGround = true;
}

void FireBall :: reboundOnSurface(){
    velocity.y = -280.0f;
}

Rectangle FireBall :: get_draw_rec(){
    const auto &frame = getFireBallFrame();
    return {position.x, position.y, frame[currentFrame].width * scale_screen, frame[currentFrame].height * scale_screen};
}

std :: vector<Rectangle> FireBall :: getFireBallFrame() const{
    if(state == FireBallState :: Explode)
        return Item_Sprite :: Fire_Ball :: Explode :: explode_;
    return Item_Sprite :: Fire_Ball :: Fly :: fly_; 
}

void FireBall :: update(float dt, const Camera2D& camera){
    if(!isActive)   return;

    if(state == FireBallState :: Explode){
        frameTimer += dt;
        if(frameTimer >= animationSpeed){
            frameTimer = 0.0f;
            currentFrame ++;

            const auto& frame = getFireBallFrame();
            if(currentFrame >= frame.size()){
                isActive = 0;
            }
        }
        return;
    }

    float gravity = 1500.0f;
    velocity.y += gravity * dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    frameTimer += dt;
    if(frameTimer >= animationSpeed){
        currentFrame ++;
        const auto& frame = getFireBallFrame();
        if(currentFrame >= frame.size()){
            currentFrame = 0;
        }
    }
    float leftEdge = camera.target.x - (Screen_w / 2.0f);
    float rightEdge = camera.target.x + Screen_w;

    if (position.x < leftEdge || position.x > rightEdge){
        isActive = false;
    }

    if(position.y > Screen_h){
        isActive = false;
    }
}

void FireBall :: draw(){
    const auto& frame = getFireBallFrame();
    if(frame.empty() || texture == nullptr) return;
    if(currentFrame >= frame.size()){
        currentFrame = 0;
    }
    
    Rectangle source = frame[currentFrame];

    Rectangle dest;
    dest.width = abs(source.width) * scale_screen;
    dest.height = abs(source.height) * scale_screen;
    dest.x = position.x;
    dest.y = position.y;
    
    DrawTexturePro(texture->sprite, source, dest, {0, 0}, 0.0f, WHITE);
}

void FireBall :: explode(){
    if(state == FireBallState :: Fly){
        state = FireBallState :: Explode;
        velocity = {0.0f, 0.0f};
        currentFrame = 0;
        frameTimer = 0.0f;
    }  
}
