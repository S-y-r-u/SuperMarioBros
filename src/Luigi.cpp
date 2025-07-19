#include "Luigi.h"

Luigi :: Luigi(Vector2 startPos) : Player(startPos){
    this -> texture = &Luigi_Sprite::luigi_sprite;
}

// Stance, Jump, Die, Walk, Slide, Climb, Crouch

std::vector<Rectangle>& Luigi :: getAnimationFrame() const{
    if(form == PlayerForm :: Small){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Small::Jump::jump_;
            case AnimationState :: Die:
                return Luigi_Sprite::Small::Die::die_;
            case AnimationState :: Walk:
                return Luigi_Sprite::Small::Walk::walk_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Small::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Small::Climb::climb_;
            default:
                return Luigi_Sprite::Small::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Super){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Super::Jump::jump_;
            case AnimationState :: Crouch:
                return Luigi_Sprite::Super::Crouch::crouch_;
            case AnimationState :: Walk:
                return Luigi_Sprite::Super::Walk::walk_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Super::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Super::Climb::climb_;
            default:
                return Luigi_Sprite::Super::Stance::stance_;
        }
    }
    return Luigi_Sprite::Small::Stance::stance_;
}