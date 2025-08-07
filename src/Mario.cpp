#include "Mario.h"

Mario ::Mario(Vector2 startPos) : Player(startPos)
{
    this->texture = &Mario_Sprite::mario_sprite;
    speed = 300.0f;
    gravity = 500.0f;
    JumpForce = -450.0f;
    friction = 0.9f;
}

Mario ::~Mario() {}

std::vector<Rectangle> &Mario ::getAnimationFrame() const
{
    if (state == AnimationState ::Small_To_Super)
        return Mario_Sprite::Small::Small_To_Super::small_to_super;

    if (state == AnimationState ::Die)
        return Mario_Sprite::Small::Die::die_;

    if (form == PlayerForm ::Small)
    {
        switch (state)
        {
        case AnimationState ::Jump:
            return Mario_Sprite::Small::Jump::jump_;
        case AnimationState ::Walk:
            return Mario_Sprite::Small::Walk::walk_;
        case AnimationState ::Slide:
            return Mario_Sprite::Small::Slide::slide_;
        case AnimationState ::Climb:
            return Mario_Sprite::Small::Climb::climb_;
        case AnimationState ::Enter_Pipe:
            return Mario_Sprite::Small::Enter_Pipe::enter_pipe;
        case AnimationState ::Fade_Out:
            return Mario_Sprite::Small::Fade_Out::fade_out;
        default:
            return Mario_Sprite::Small::Stance::stance_;
        }
    }
    else if (form == PlayerForm ::Invincible)
    {
        switch (state)
        {
        case AnimationState ::Jump:
            return Mario_Sprite::Invincible::Jump::jump_;
        case AnimationState ::Walk:
            return Mario_Sprite::Invincible::Walk::walk_;
        case AnimationState ::Slide:
            return Mario_Sprite::Invincible::Slide::slide_;
        case AnimationState ::Climb:
            return Mario_Sprite::Invincible::Climb::climb_;
        case AnimationState ::Enter_Pipe:
            return Mario_Sprite::Invincible::Enter_Pipe::enter_pipe;
        case AnimationState ::Small_To_Super:
            return Mario_Sprite::Invincible::Small_To_Super::small_to_super;
        default:
            return Mario_Sprite::Invincible::Stance::stance_;
        }
    }
    else if (form == PlayerForm ::Super)
    {
        switch (state)
        {
        case AnimationState ::Jump:
            return Mario_Sprite::Super::Jump::jump_;
        case AnimationState ::Jump_To_Fire:
            return Mario_Sprite::Super::Jump_To_Fire::jump_to_fire;
        case AnimationState ::Crouch:
            return Mario_Sprite::Super::Crouch::crouch_;
        case AnimationState ::Crouch_To_Fire:
            return Mario_Sprite::Super::Crouch_To_Fire::crouch_to_fire;
            ;
        case AnimationState ::Walk:
            return Mario_Sprite::Super::Walk::walk_;
        case AnimationState ::Walk_To_Fire:
            return Mario_Sprite::Super::Walk_To_Fire::walk_to_fire;
        case AnimationState ::Slide:
            return Mario_Sprite::Super::Slide::slide_;
        case AnimationState ::Slide_To_Fire:
            return Mario_Sprite::Super::Slide_To_Fire::slide_to_fire;
        case AnimationState ::Climb:
            return Mario_Sprite::Super::Climb::climb_;
        case AnimationState ::Enter_Pipe:
            return Mario_Sprite::Super::Enter_Pipe::enter_pipe;
        case AnimationState ::Fade_Out:
            return Mario_Sprite::Super::Fade_Out::fade_out;
        case AnimationState ::Hit:
            return Mario_Sprite::Super::Hit::hit_;
        case AnimationState ::Stance_To_Fire:
            return Mario_Sprite::Super::Stance_To_Fire::stance_to_fire;
        default:
            return Mario_Sprite::Super::Stance::stance_;
        }
    }
    else if (form == PlayerForm ::Invincible_Super_And_Fire)
    {
        switch (state)
        {
        case AnimationState ::Jump:
            return Mario_Sprite::Invincible_Super_And_Fire::Jump::jump_;
        case AnimationState ::Crouch:
            return Mario_Sprite::Invincible_Super_And_Fire::Crouch::crouch_;
        case AnimationState ::Slide:
            return Mario_Sprite::Invincible_Super_And_Fire::Slide::slide_;
        case AnimationState ::Climb:
            return Mario_Sprite::Invincible_Super_And_Fire::Climb::climb_;
        case AnimationState ::Shoot_Fire:
            return Mario_Sprite::Invincible_Super_And_Fire::Shoot_Fire::shoot_fire;
        case AnimationState ::Walk:
            return Mario_Sprite::Invincible_Super_And_Fire::Walk::walk_;
        case AnimationState ::Enter_Pipe:
            return Mario_Sprite::Invincible_Super_And_Fire::Enter_Pipe::enter_pipe;
        default:
            return Mario_Sprite::Invincible_Super_And_Fire::Stance::stance_;
        }
    }
    else if (form == PlayerForm ::Fire)
    {
        switch (state)
        {
        case AnimationState ::Jump:
            return Mario_Sprite::Fire::Jump::jump_;
        case AnimationState ::Crouch:
            return Mario_Sprite::Fire::Crouch::crouch_;
        case AnimationState ::Walk:
            return Mario_Sprite::Fire::Walk::walk_;
        case AnimationState ::Slide:
            return Mario_Sprite::Fire::Slide::slide_;
        case AnimationState ::Climb:
            return Mario_Sprite::Fire::Climb::climb_;
        case AnimationState ::Shoot:
            return Mario_Sprite::Fire::Shoot::shoot_;
        case AnimationState ::Enter_Pipe:
            return Mario_Sprite::Fire::Enter_Pipe::enter_pipe;
        case AnimationState ::Fade_Out:
            return Mario_Sprite::Fire::Fade_Out::fade_out;
        case AnimationState ::Hit:
            return Mario_Sprite::Fire::Hit::hit_;
        default:
            return Mario_Sprite::Fire::Stance::stance_;
        }
    }

    return Mario_Sprite::Small::Stance::stance_;
}