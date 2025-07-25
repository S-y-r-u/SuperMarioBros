#include "Luigi.h"

Luigi :: Luigi(Vector2 startPos) : Player(startPos){
    this -> texture = &Luigi_Sprite::luigi_sprite;
    speed = 160.0f;     // chạy nhanh
    gravity = 450.0f;   // rơi chậm
    JumpForce = -500.0f;    // nhảy cao 
    friction = 0.96f;   // trượt xa hơn 
}

std::vector<Rectangle>& Luigi :: getAnimationFrame() const{
    if(state == AnimationState :: Small_To_Super)
        return Luigi_Sprite::Small::Small_To_Super::small_to_super;
    
    if(state == AnimationState :: Die)
        return Luigi_Sprite::Small::Die::die_;

    if(form == PlayerForm :: Small){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Small::Jump::jump_;
            case AnimationState :: Walk:
                return Luigi_Sprite::Small::Walk::walk_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Small::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Small::Climb::climb_;
            case AnimationState :: Enter_Pipe:
                return Luigi_Sprite::Small::Enter_Pipe::enter_pipe;
            case AnimationState :: Fade_Out:
                return Luigi_Sprite::Small::Fade_Out::fade_out;
            default:
                return Luigi_Sprite::Small::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Invincible){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Invincible::Jump::jump_;
            case AnimationState :: Walk:
                return Luigi_Sprite::Invincible::Walk::walk_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Invincible::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Invincible::Climb::climb_;
            case AnimationState :: Enter_Pipe:
                return Luigi_Sprite::Invincible::Enter_Pipe::enter_pipe;
            case AnimationState :: Small_To_Super:
                return Luigi_Sprite::Invincible::Small_To_Super::small_to_super;
            default:
                return Luigi_Sprite::Invincible::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Super){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Super::Jump::jump_;
            case AnimationState :: Jump_To_Fire:
                return Luigi_Sprite::Super::Jump_To_Fire::jump_to_fire;
            case AnimationState :: Crouch:
                return Luigi_Sprite::Super::Crouch::crouch_;
            case AnimationState :: Crouch_To_Fire:
                return Luigi_Sprite::Super::Crouch_To_Fire::crouch_to_fire;;
            case AnimationState :: Walk:
                return Luigi_Sprite::Super::Walk::walk_;
            case AnimationState :: Walk_To_Fire:
                return Luigi_Sprite::Super::Walk_To_Fire::walk_to_fire;
            case AnimationState :: Slide:
                return Luigi_Sprite::Super::Slide::slide_;
            case AnimationState :: Slide_To_Fire:
                return Luigi_Sprite::Super::Slide_To_Fire::slide_to_fire;
            case AnimationState :: Climb:
                return Luigi_Sprite::Super::Climb::climb_;
            case AnimationState :: Enter_Pipe:
                return Luigi_Sprite::Super::Enter_Pipe::enter_pipe;
            case AnimationState :: Fade_Out:
                return Luigi_Sprite::Super::Fade_Out::fade_out;
            case AnimationState :: Hit:
                return Luigi_Sprite::Super::Hit::hit_;
            case AnimationState :: Stance_To_Fire:
                return Luigi_Sprite::Super::Stance_To_Fire::stance_to_fire;
            default:
                return Luigi_Sprite::Super::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Invincible_Super_And_Fire){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Invincible_Super_And_Fire::Jump::jump_;
            case AnimationState :: Crouch:
                return Luigi_Sprite::Invincible_Super_And_Fire::Crouch::crouch_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Invincible_Super_And_Fire::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Invincible_Super_And_Fire::Climb::climb_;
            case AnimationState :: Shoot_Fire:
                return Luigi_Sprite::Invincible_Super_And_Fire::Shoot_Fire::shoot_fire;
            case AnimationState :: Walk:
                return Luigi_Sprite::Invincible_Super_And_Fire::Walk::walk_;
            case AnimationState :: Enter_Pipe:
                return Luigi_Sprite::Invincible_Super_And_Fire::Enter_Pipe::enter_pipe;
            default:
                return Luigi_Sprite::Invincible_Super_And_Fire::Stance::stance_;
        }
    }
    else if(form == PlayerForm :: Fire){
        switch(state){
            case AnimationState :: Jump:
                return Luigi_Sprite::Fire::Jump::jump_;
            case AnimationState :: Crouch:
                return Luigi_Sprite::Fire::Crouch::crouch_;
            case AnimationState :: Walk:
                return Luigi_Sprite::Fire::Walk::walk_;
            case AnimationState :: Slide:
                return Luigi_Sprite::Fire::Slide::slide_;
            case AnimationState :: Climb:
                return Luigi_Sprite::Fire::Climb::climb_;
            case AnimationState :: Shoot:
                return Luigi_Sprite::Fire::Shoot::shoot_;
            case AnimationState :: Enter_Pipe:
                return Luigi_Sprite::Fire::Enter_Pipe::enter_pipe;
            case AnimationState :: Fade_Out:
                return Luigi_Sprite::Fire::Fade_Out::fade_out;
            case AnimationState :: Hit:
                return Luigi_Sprite::Fire::Hit::hit_;
            default:
                return Luigi_Sprite::Fire::Stance::stance_;
        }
    }
    
    return Luigi_Sprite::Small::Stance::stance_;
}