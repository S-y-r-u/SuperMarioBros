#include "Player.h"
#include <cmath>

Player :: Player(Vector2 startPos) : Character(startPos){
    velocity = {0.0f , 0.0f};
    isFacingLeft = 0;
    speed = 150.0f;
    form = PlayerForm :: Small;
    state = AnimationState :: Stance;
    currentFrame = 0;
    frameTimer = 0.0f;
    animationSpeed = 1.0f/12.0f;
}

Player :: ~Player(){}

void Player :: MoveRight(){
    velocity.x = speed;
    isFacingLeft = 0;
}

void Player :: MoveLeft(){
    velocity.x = -speed;
    isFacingLeft = 1;
}


void Player :: update(float dt){
    position.x += velocity.x * dt;

    if(velocity.x != 0.0f)   state = AnimationState :: Walk;
    else state = AnimationState :: Stance;

    frameTimer += dt;
    if(frameTimer >= animationSpeed){
        frameTimer = 0.0f;
        currentFrame++;

        const auto& frame = getAnimationFrame();
        if(currentFrame >= frame.size()) currentFrame = 0;
    }
}

void Player :: draw(){
    const auto& frame = getAnimationFrame();

    if(frame.empty() || texture == nullptr) return;
    if(currentFrame >= frame.size()){
        currentFrame = 0;
    }

    Rectangle source = frame[currentFrame];
    if(isFacingLeft){
        source.width *= (-1);
    }

    float scale = 3.0f;
    Rectangle dest;
    dest.width = abs(source.width) * scale;
    dest.height = abs(source.height) * scale;
    dest.x = position.x - dest.width/2.0f;
    dest.y = position.y - dest.height;
    
    DrawTexturePro(*texture, source, dest, {0, 0}, 0.0f, WHITE);
}
