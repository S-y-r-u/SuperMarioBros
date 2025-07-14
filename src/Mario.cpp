#include "Mario.h"
#include "sprite.h"

Mario :: Mario(Vector2 startPos) : Player(startPos){
    this -> texture = &Mario_Sprite::mario_sprite.sprite;
}

// Stance, Jump, Die, Walk, Slide, Climb, Crouch

std::vector<Rectangle>& Mario :: getAnimationFrame() const{
    if(form == PlayerForm :: Small){
        switch(state){
            case AnimationState :: Jump:
                return Mario_Sprite::Small::Jump::jump_;
            case AnimationState :: Die:
                return Mario_Sprite::Small::Die::die_;
            case AnimationState :: Walk:
                return Mario_Sprite::Small::Walk::walk_;
            case AnimationState :: Slide:
                return Mario_Sprite::Small::Slide::slide_;
            case AnimationState :: Climb:
                return Mario_Sprite::Small::Climb::climb_;
            default:
                return Mario_Sprite::Small::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Super){
        switch(state){
            case AnimationState :: Jump:
                return Mario_Sprite::Super::Jump::jump_;
            case AnimationState :: Crouch:
                return Mario_Sprite::Super::Crouch::crouch_;
            case AnimationState :: Walk:
                return Mario_Sprite::Super::Walk::walk_;
            case AnimationState :: Slide:
                return Mario_Sprite::Super::Slide::slide_;
            case AnimationState :: Climb:
                return Mario_Sprite::Super::Climb::climb_;
            default:
                return Mario_Sprite::Super::Stance::stance_;
        }
    }
    return Mario_Sprite::Small::Stance::stance_;
}