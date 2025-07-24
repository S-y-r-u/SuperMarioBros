#include "Player.h"
#include <cmath>

Player :: Player(Vector2 startPos) : Character(startPos){
    velocity = {0.0f , 0.0f};
    isFacingLeft = 0;
    isGround = 1;
    speed = 150.0f;
    gravity = 500.0f;
    form = PlayerForm :: Small;
    state = AnimationState :: Stance;
    currentFrame = 0;
    frameTimer = 0.0f;
    animationSpeed = 1.0f/12.0f;
}

Player :: ~Player(){}

Rectangle Player :: get_draw_rec(){
    const auto& frame = getAnimationFrame();
    return {position.x, position.y, frame[currentFrame].width * scale_screen, frame[currentFrame].height * scale_screen};
}

AnimationState Player :: get_state() const{
    return state;
}

PlayerForm Player :: get_form() const{
    return form;
}

void Player :: MoveRight(){
    velocity.x = speed;
    isFacingLeft = 0;
}

void Player :: MoveLeft(){
    velocity.x = -speed;
    isFacingLeft = 1;
}

void Player :: StopMoving(){
    velocity.x = 0.0f;
}

void Player :: Jump(){
    if(!isGround) return;
    isGround = 0;
    velocity.y = -500;
}

void Player :: update(float dt){
    position.x += velocity.x * dt;
    velocity.y += gravity * dt;
    position.y += velocity.y * dt;

    if(velocity.x != 0.0f)   state = AnimationState :: Walk;
    else state = AnimationState :: Stance;

    frameTimer += dt;
    if(frameTimer >= animationSpeed){
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % getAnimationFrame().size();
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

    Rectangle dest;
    dest.width = abs(source.width) * scale_screen;
    dest.height = abs(source.height) * scale_screen;
    dest.x = position.x;
    dest.y = position.y;
    
    DrawTexturePro(texture->sprite, source, dest, {0, 0}, 0.0f, WHITE);
}

void Player :: collectCoin(){

}

void Player :: getMushroom(){
    if(form == PlayerForm :: Small){
        form = PlayerForm :: Super;
        state = AnimationState::Small_To_Super;
    } 
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Player :: getFlower(){
    if(form != PlayerForm :: Fire){
        if(form == PlayerForm :: Small){
            state = AnimationState::Small_To_Super;
        }
        else{
            state = AnimationState::Stance_To_Fire; 
        }
    }
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Player :: getStar(){
    
    currentFrame = 0;
    frameTimer = 0.0f;
}