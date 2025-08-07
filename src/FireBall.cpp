#include "FireBall.h"

FireBall :: FireBall(Vector2 pos, bool facingLeft){
    position = pos;
    this -> texture = &Item_Sprite::item_;

    isActive = 1;
    state = FireBallState :: Fly;
    float speedX = 300.0f, speedY = -180.0f;
    if(facingLeft)  velocity = {-speedX, speedY};
    else velocity = {speedX, speedY};

    currentFrame = 0;
    frameTimer = 0.0f;
    animationSpeed = 1.0/12.0;
}

FireBall :: ~FireBall(){

}

bool FireBall :: getActive() const{
    return isActive;
}

std :: vector<Rectangle> FireBall :: getFireBallFrame() const{
    if(state == FireBallState :: Explode)
        return Item_Sprite :: Fire_Ball :: Explode :: explode_;
    return Item_Sprite :: Fire_Ball :: Fly :: fly_; 
}

void FireBall :: update(float dt){
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

    float gravity = 500.0f;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // nay len san nha
    if (position.y > 579){ 
        position.y = 579;
        velocity.y = -250.0f;
    }

    frameTimer += dt;
    if(frameTimer >= animationSpeed){
        currentFrame ++;
        const auto& frame = getFireBallFrame();
        if(currentFrame >= frame.size()){
            currentFrame = 0;
        }
    }

    if(position.x < 0 || position.x > GetScreenWidth()){
        isActive = 0;
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
