#include "Enemy/KoopaTroopaState.h"
#include "Enemy/KoopaTroopa.h"

// Common function
void KoopaState::OnFired(KoopaTroopa *koopa)
{
    koopa->SetState(new KoopaDyingState());
}

// ---------- WALKING ----------
void KoopaWalkingState::Enter(KoopaTroopa *koopa)
{

    koopa->animation_.Set_Frames(Enemies_Sprite::Troopa_Green::Normal::normal_);
    koopa->animation_.Set_Frame_Speed(1 / 6.0f);
    koopa->velocity_.x = -75.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->gravity_ = 1000.0f;
    koopa->score = 100;
}

void KoopaWalkingState::Update(KoopaTroopa *koopa, float dt)
{
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
    // std::cout << koopa->velocity_.y << std::endl;
    koopa->animation_.Update(dt);
}

void KoopaWalkingState::OnStomped(KoopaTroopa *koopa)
{
    koopa->SetState(new KoopaShellIdleState());
}

void KoopaWalkingState::Apply_AI(KoopaTroopa *koopa, MapManagement &map)
{
    if (koopa->is_ground == false)
        return;
    Rectangle koopaRec = koopa->Get_Draw_Rec();
    Vector2 next_pos;
    if (koopa->velocity_.x > 0)
        next_pos = {koopaRec.x + koopaRec.width, koopa->position_.y + 10.0f};
    else
        next_pos = {koopaRec.x, koopa->position_.y + 10.0f};
    int row = static_cast<int>(next_pos.y / Tile_Size);
    int col = static_cast<int>(next_pos.x / Tile_Size);
    if (map.GetTile(col, row) == 0)
    {
        koopa->Notify_Change_Direct();
    }
}

// ---------- SHELL IDLE ----------
void KoopaShellIdleState::Enter(KoopaTroopa *koopa)
{
    koopa->animation_.Set_Frames(Enemies_Sprite::Troopa_Green::Shell_Idle::shell_idle);
    koopa->velocity_.y = -100.f; // dừng lại
    koopa->velocity_.x = 0;
    timer = 0.0f;
    koopa->score = 100;
}

void KoopaShellIdleState::Update(KoopaTroopa *koopa, float dt)
{
    immobile_timer += dt;
    timer += dt;

    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity

    if (timer >= 3.0f && timer < 5.0f)
    {
        koopa->animation_.Set_Frame(1);
    }
    else if (timer >= 5.0f)
    {
        koopa->SetState(new KoopaWalkingState());
    }
}

void KoopaShellIdleState::OnStomped(KoopaTroopa *koopa)
{
    OnKicked(koopa, 1); // Khi bị giẫm sẽ chuyển sang trạng thái shell moving
}

void KoopaShellIdleState::OnKicked(KoopaTroopa *koopa, int direction)
{
    if (immobile_timer >= InChange_Frame_Time)
    {
        koopa->velocity_.x = 1.0f * direction;        // Set velocity based on kick direction
        koopa->SetState(new KoopaShellMovingState()); // Chuyển sang trạng thái shell
    }
}

// ---------- SHELL MOVING ----------
void KoopaShellMovingState::Enter(KoopaTroopa *koopa)
{
    koopa->animation_.Set_Frames(Enemies_Sprite::Troopa_Green::Shell_Moving::shell_moving);
    koopa->animation_.Set_Frame_Speed(1 / 6.0f);
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 600.0f : -600.0f;
    koopa->velocity_.y = 0; // dừng lại
    koopa->score = 100;
}

void KoopaShellMovingState::Update(KoopaTroopa *koopa, float dt)
{
    koopa->animation_.Update(dt);
    koopa->velocity_.y += koopa->gravity_ * dt; // apply gravity
}

void KoopaShellMovingState::OnStomped(KoopaTroopa *koopa)
{
    // đá lại thì dừng
    koopa->SetState(new KoopaShellIdleState());
}

// ---------- DYING ----------
void KoopaDyingState::Enter(KoopaTroopa *koopa)
{
    koopa->animation_.Set_Rec(Enemies_Sprite::Troopa_Green::be_dying);
    koopa->velocity_.x = 0;
    koopa->velocity_.y = -200.0f; // upward movement
    koopa->is_dead = true;
    koopa->gravity_ = 1000.0f;
    if (koopa->previous_state && dynamic_cast<KoopaFlyingState *>(koopa->previous_state))
    {
        koopa->score = 300;
    }
    else if (koopa->previous_state && dynamic_cast<KoopaWalkingState *>(koopa->previous_state))
    {
        koopa->score = 200;
    }
    else if (koopa->previous_state && dynamic_cast<KoopaShellIdleState *>(koopa->previous_state))
    {
        koopa->score = 100;
    }
}

void KoopaDyingState::Update(KoopaTroopa *koopa, float dt)
{
    // gravity đã xử lý ngoài

    koopa->velocity_.y += koopa->gravity_ * dt;
    if (koopa->position_.y >= Screen_h * scale_screen)
    {
        koopa->is_active = false;
    }
}

//_______Flying _______________
void KoopaFlyingState::Enter(KoopaTroopa *koopa)
{
    koopa->animation_.Set_Frames(Enemies_Sprite::Troopa_Green::Flying::flying_);
    koopa->animation_.Set_Frame_Speed(0.5f);
    koopa->velocity_.x = (koopa->velocity_.x >= 0) ? 90.0f : -90.0f;
    koopa->velocity_.y = 0; // bay lên ban đầu
    koopa->gravity_ = 600.0f;
    koopa->score = 0;
}

void KoopaFlyingState::Update(KoopaTroopa *koopa, float dt)
{
    if (koopa->is_ground)
    {
        koopa->velocity_.y = -fly_speed; // nếu chạm đất thì bay lên
        koopa->is_ground = false;        // không còn trên mặt đất
    }
    koopa->velocity_.y += koopa->gravity_ * dt; // áp dụng trọng lực

    koopa->animation_.Update(dt);
}

void KoopaFlyingState::OnStomped(KoopaTroopa *koopa)
{
    // Khi bị giẫm sẽ thành shell
    koopa->SetState(new KoopaWalkingState());
}

void KoopaFlyingState::Apply_AI(KoopaTroopa *koopa, MapManagement &map)
{
    Rectangle koopaRec = koopa->Get_Draw_Rec();
    Vector2 next_pos;
    if (koopa->velocity_.x > 0)
        next_pos = {koopaRec.x + koopaRec.width, koopa->position_.y + 10.0f};
    else
        next_pos = {koopaRec.x, koopa->position_.y + 10.0f};
    int col = next_pos.x / Tile_Size;
    bool is_change = true;
    for (int i = 0; i < map.GetHeight(); i++)
    {
        if (map.GetTile(col, i) != 0)
        {
            is_change = false;
            break;
        }
    }
    if (is_change)
        koopa->Notify_Change_Direct();
}
