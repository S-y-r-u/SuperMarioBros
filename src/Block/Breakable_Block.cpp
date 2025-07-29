#include "Block/Breakable_Block.h"

Breakable_BLock::Breakable_BLock(Block &block)
    : m_block(block), delta_time(0.0f), is_delete(false), rotation(0.0f)
{
    rec_ = Item_Sprite::Brown_Brick::break_;
    before_pos = {m_block.Get_Pos().x, m_block.Get_Pos().y - rec_.height};
    up_pos_left = down_pos_left = before_pos;
}

void Breakable_BLock::Draw_()
{
    Vector2 origin = {rec_.width * scale_screen / 2.0f, rec_.height * scale_screen / 2.0f};

    Rectangle dest_rec_up_left = {
        up_pos_left.x,
        up_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_up_right = {
        before_pos.x + (before_pos.x - up_pos_left.x),
        up_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_down_left = {
        down_pos_left.x,
        down_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_down_right = {
        before_pos.x + (before_pos.x - down_pos_left.x),
        down_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_up_left, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_up_right, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_down_left, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_down_right, origin, rotation, WHITE);
}

void Breakable_BLock::Update_()
{
    Fall_();
    Be_Delete();
}

bool Breakable_BLock::Get_Elapse() { return false; }

bool Breakable_BLock::Get_Is_Delete() const { return is_delete; }

void Breakable_BLock::Fall_()
{
    delta_time += 0.16f;

    float up_delta_y = -Break_Height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
    float down_delta_y = 0.5f * delta_time * delta_time * Physics::gravity_;

    up_pos_left.y = before_pos.y + up_delta_y;
    up_pos_left.x -= Move_ * GetFrameTime();

    down_pos_left.y = before_pos.y + down_delta_y;
    down_pos_left.x -= Move_ * GetFrameTime();

    rotation += Rotation_Speed;
    if (rotation >= 360.0f)
        rotation = 0.0f;
}

void Breakable_BLock::Be_Delete()
{
    if (up_pos_left.y - rec_.height * scale_screen / 2.0f >= Screen_h)
        is_delete = true;
}

Rectangle Breakable_BLock::Get_Draw_Rec() const { return {m_block.Get_Pos().x - rec_.width * scale_screen / 2.0f, m_block.Get_Pos().y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }
