#include "Player.h"
#include <cmath>

Player ::Player(Vector2 startPos) : Character(startPos)
{
    velocity = {0.0f, 0.0f};
    speed = 150.0f;
    gravity = 500.0f;
    JumpForce = -450.0f;
    friction = 0.9f;

    form = PlayerForm ::Small;
    state = AnimationState ::Stance;
    isTransforming = 0;
    targetForm = form;

    isInvincible = 0;
    invincibleTimer = 0.0f;
    beforeStar = form;

    isDead = 0;
    isActive = 1;
    deadTimer = 0.0f;

    fireCoolDown = 0.0f;

    currentFrame = 0;
    frameTimer = 0.0f;
    animationSpeed = 1.0f / 12.0f;
}

Player ::~Player() {}

Rectangle Player ::get_draw_rec()
{
    const auto &frame = getAnimationFrame();
    return {position.x, position.y, frame[currentFrame].width * scale_screen, frame[currentFrame].height * scale_screen};
}

Rectangle Player::Get_Previous_Rec()
{
    return previous_frame_rec;
}

void Player ::Set_isGround(bool value)
{
    isGround = value;
}

void Player ::MoveRight()
{
    velocity.x = speed;
    isFacingLeft = 0;
}

void Player ::MoveLeft()
{
    velocity.x = -speed;
    isFacingLeft = 1;
}

void Player ::StopMoving()
{
    velocity.x = 0.0f;
}

void Player ::Jump()
{
    if (!isGround)
        return;
    isGround = 0;
    velocity.y = JumpForce;
    if (form == PlayerForm ::Small)
    {
        SoundManager::GetInstance().PlaySoundEffect("jump-small");
    }
    else if (form == PlayerForm ::Super)
    {
        SoundManager::GetInstance().PlaySoundEffect("jump-super");
    }
}

void Player ::Cut_Jump()
{
    if (velocity.y < 0.0f)
    {
        velocity.y *= 0.6f;
    }
}

void Player ::update(float dt)
{
    previous_frame_rec = getAnimationFrame()[currentFrame];

    if (isTransforming)
    {
        frameTimer += dt;
        if (frameTimer >= animationSpeed)
        {
            frameTimer = 0.0f;
            currentFrame++;
            const auto &frame = getAnimationFrame();

            if (currentFrame >= frame.size())
            {
                isTransforming = 0;
                form = targetForm;
                state = AnimationState ::Stance;
                currentFrame = 0;
            }
        }
        position.y = position.y + (previous_frame_rec.height - getAnimationFrame()[currentFrame].height) * scale_screen;
        return;
    }

    if (isInvincible)
    {
        invincibleTimer -= dt;
        if (invincibleTimer <= 0.0f)
        {
            isInvincible = 0;
            form = beforeStar;
        }
    }

    const auto &frame = getAnimationFrame();
    if(position.y >= Screen_h)
        isActive = 0;

    if (isDead)
    {
        velocity.y += gravity * dt;
        position.y += velocity.y * dt;

        if (deadTimer >= 0.0f)
            deadTimer -= dt;
        return;
    }

    velocity.y += gravity * dt;

    // ma sát tru?t
    if (velocity.x != 0.0f)
    {
        velocity.x *= pow(friction, dt * 60);
        if (abs(velocity.x) < 1.0f)
            velocity.x = 0.0f;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (isGround)
    {
        if (velocity.x != 0.0f)
            state = AnimationState ::Walk;
        else
            state = AnimationState ::Stance;
    }
    else
    {
        state = AnimationState ::Jump;
        // if (IsKeyReleased(KEY_W))
        // {
        //     velocity.y *= 0.5f; // Giảm tốc độ nhảy khi nhả phím W
        // }
    }

    if (currentFrame >= getAnimationFrame().size())
        currentFrame = 0;
    frameTimer += dt;
    if (frameTimer >= animationSpeed)
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % getAnimationFrame().size();
    }
    position.y = position.y + (previous_frame_rec.height - getAnimationFrame()[currentFrame].height) * scale_screen;
}

void Player ::draw()
{
    const auto &frame = getAnimationFrame();

    if (frame.empty() || texture == nullptr)
        return;
    if (currentFrame >= frame.size())
    {
        currentFrame = 0;
    }

    Rectangle source = frame[currentFrame];
    if (isFacingLeft)
    {
        source.width *= (-1);
    }

    Rectangle dest;
    dest.width = abs(source.width) * scale_screen;
    dest.height = abs(source.height) * scale_screen;
    dest.x = position.x;
    dest.y = position.y;
    DrawTexturePro(texture->sprite, source, dest, {0, 0}, 0.0f, WHITE);
}

void Player ::collectCoin()
{
}

void Player ::getMushroom()
{
    if (isTransforming || form != PlayerForm ::Small)
        return;

    isTransforming = 1;
    state = AnimationState::Small_To_Super;
    targetForm = PlayerForm ::Super;

    velocity = {0.0f, 0.0f};
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Player ::getFlower()
{
    if (isTransforming || form == PlayerForm ::Fire)
        return;

    if (isInvincible)
        beforeStar = PlayerForm::Fire;
    else
    {
        isTransforming = 1;
        targetForm = PlayerForm ::Fire;

        if (form == PlayerForm ::Small)
        {
            state = AnimationState::Small_To_Super;
        }
        else if (form == PlayerForm ::Super)
        {
            state = AnimationState::Stance_To_Fire;
        }

        velocity = {0.0f, 0.0f};
        currentFrame = 0;
        frameTimer = 0.0f;
    }
}

void Player ::getStar()
{
    if (isTransforming)
        return;
    if (isInvincible)
    {
        invincibleTimer = 10.0f;
        return;
    }

    isInvincible = 1;
    invincibleTimer = 10.0f;
    beforeStar = form;

    if (form == PlayerForm ::Fire || form == PlayerForm ::Super)
        form = PlayerForm ::Invincible_Super_And_Fire;
    else
        form = PlayerForm ::Invincible;
}

void Player ::Die()
{
    if (isDead)
        return;
    isDead = 1;
    state = AnimationState ::Die;

    velocity = {0.0f, -350.0f};
    currentFrame = 0;
    frameTimer = 0.0f;
    deadTimer = 3.0f;
}


void Player :: updateCoolDown(float dt)
{
    if(fireCoolDown >= 0.0f)  fireCoolDown -= dt; 
}

void Player :: Shoot(std::vector<FireBall*> &fireballs)
{
    bool canShoot = (form == PlayerForm :: Fire || form == PlayerForm :: Invincible_Super_And_Fire);
    if(!canShoot || isTransforming || isDead || fireCoolDown > 0 || fireballs.size() >= 3){
        return;
    }

    state = AnimationState :: Shoot;
    fireCoolDown = 0.3f;
    currentFrame = 0;
    frameTimer = 0.0f;

    Vector2 fireBallStartPos = position;
    Rectangle playerPos = get_draw_rec();

    fireBallStartPos.y += playerPos.height * 0.6f;
    if(!isFacingLeft)    fireBallStartPos.x += playerPos.width - 15;
    else fireBallStartPos.x += 5;

    fireballs.push_back(new FireBall(fireBallStartPos, isFacingLeft));
}