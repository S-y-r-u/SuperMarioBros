#include "Player.h"
#include <cmath>

Player :: Player(Vector2 startPos) : Character(startPos){
    velocity = {0.0f , 0.0f};
    speed = 150.0f;
    gravity = 500.0f;
    JumpForce = -450.0f;
    friction = 0.9f;
    
    form = PlayerForm :: Small;
    state = AnimationState :: Stance;
    isTransforming = 0;
    targetForm = form;

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
    velocity.y = JumpForce;
}

void Player :: update(float dt){
    if(isTransforming){
        frameTimer += dt;
        if(frameTimer >= animationSpeed){
            frameTimer = 0.0f;
            currentFrame++;
            const auto& frame = getAnimationFrame();

            if(currentFrame >= frame.size()){
                isTransforming = 0;
                form = targetForm;
                state = AnimationState :: Stance;
                currentFrame = 0;
            }
        }
        return;
    }

    velocity.y += gravity * dt;

    // ma sát tru?t
    if(velocity.x != 0.0f){
        velocity.x *= pow(friction, dt*60);
        if(abs(velocity.x) < 1.0f)   velocity.x = 0.0f;
    }
    
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if(isGround){
        if(velocity.x != 0.0f)   state = AnimationState :: Walk;
        else state = AnimationState :: Stance;
    }
    else state = AnimationState :: Jump;
    if (currentFrame >= getAnimationFrame().size())
        currentFrame = 0;
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
    if(isTransforming || form != PlayerForm :: Small)   return;

    isTransforming = 1;
    state = AnimationState::Small_To_Super;
    targetForm = PlayerForm :: Super;
    
    velocity = {0.0f, 0.0f};
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Player :: getFlower(){
    if(isTransforming || form == PlayerForm :: Fire)    return;

    isTransforming = 1;
    targetForm = PlayerForm :: Fire;

    if(form == PlayerForm :: Small){
        state = AnimationState::Small_To_Super;
    }
    else if(form == PlayerForm :: Super){
        state = AnimationState::Stance_To_Fire; 
    }
    
    velocity = {0.0f, 0.0f};
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Player :: getStar(){
    
    currentFrame = 0;
    frameTimer = 0.0f;
}   