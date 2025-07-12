#include "Mario.h"
#include "sprite.h"

Mario :: Mario(Vector2 startPos) : Player(startPos){
    this -> texture = &Mario::mario_sprite.sprite;
}

// Stance, Jump, Die, Walk, Slide, Climb, Crouch

std::vector<Rectangle>& Mario :: getAnimationFrame() const{
    if(form == PlayerForm :: Small){
        switch(state){
            case AnimationState :: Jump:
                return Mario::Small::Jump::jump_;
            case AnimationState :: Die:
                return Mario::Small::Die::die_;
            case AnimationState :: Walk:
                return Mario::Small::Walk::walk_;
            case AnimationState :: Slide:
                return Mario::Small::Slide::slide_;
            case AnimationState :: Climb:
                return Mario::Small::Climb::climb_;
            default:
                return Mario::Small::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Super){
        switch(state){
            case AnimationState :: Jump:
                return Mario::Super::Jump::jump_;
            case AnimationState :: Crouch:
                return Mario::Super::Crouch::crouch_;
            case AnimationState :: Walk:
                return Mario::Super::Walk::walk_;
            case AnimationState :: Slide:
                return Mario::Super::Slide::slide_;
            case AnimationState :: Climb:
                return Mario::Super::Climb::climb_;
            default:
                return Mario::Super::Stance::stance_;
        }
    }
    return Mario::Small::Stance::stance_;
}