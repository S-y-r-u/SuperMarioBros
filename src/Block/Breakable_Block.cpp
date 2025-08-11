#include "Block/Breakable_Block.h"

Breakable_BLock::Breakable_BLock(Block &block)
    : A_Block_State(&Item_Sprite::item_),
      m_block(block),
      is_delete(false),
      rotation(0.0f)
{
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Brown_Brick::break_);
    before_pos = {m_block.Get_Pos().x, m_block.Get_Pos().y - animation_.Get_Current_Rec().height};
    up_pos_left = down_pos_left = before_pos;

    up_velocity = {-Move_, -Break_Height}; // bay lên
    down_velocity = {-Move_, 0.0f};        // rơi xuống từ từ
}

void Breakable_BLock::Draw_()
{
    Vector2 origin = {animation_.Get_Current_Rec().width * scale_screen / 2.0f, animation_.Get_Current_Rec().height * scale_screen / 2.0f};

    Rectangle dest_rec_up_left = {
        up_pos_left.x,
        up_pos_left.y,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};

    Rectangle dest_rec_up_right = {
        before_pos.x + (before_pos.x - up_pos_left.x),
        up_pos_left.y,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};

    Rectangle dest_rec_down_left = {
        down_pos_left.x,
        down_pos_left.y,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};

    Rectangle dest_rec_down_right = {
        before_pos.x + (before_pos.x - down_pos_left.x),
        down_pos_left.y,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};

    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec_up_left, origin, rotation, WHITE);
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec_up_right, origin, rotation, WHITE);
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec_down_left, origin, rotation, WHITE);
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec_down_right, origin, rotation, WHITE);
}

void Breakable_BLock::Update_()
{
    Fall_();
    Be_Delete();
    animation_.Update(GetFrameTime());
}

bool Breakable_BLock::Get_Elapse() { return true; }

bool Breakable_BLock::Get_Is_Delete() const { return is_delete; }

void Breakable_BLock::Fall_()
{
    float dt = GetFrameTime();

    // Cập nhật vận tốc theo gia tốc trọng lực
    up_velocity.y += Physics::gravity_ * dt;
    down_velocity.y += Physics::gravity_ * dt;

    // Cập nhật vị trí
    up_pos_left.x += up_velocity.x * dt;
    up_pos_left.y += up_velocity.y * dt;
    // Này bên trên trái

    down_pos_left.x += down_velocity.x * dt;
    down_pos_left.y += down_velocity.y * dt;
    // Này bên dưới trái

    // Cố định block gốc để không vẽ nữa
    m_block.Set_Pos({0, 0});

    // Xoay
    rotation += Rotation_Speed;
    if (rotation >= 360.0f)
        rotation = 0.0f;
}

void Breakable_BLock::Be_Delete()
{
    if (up_pos_left.y - animation_.Get_Current_Rec().height * scale_screen / 2.0f >= Screen_h)
        is_delete = true;
}

Rectangle Breakable_BLock::Get_Draw_Rec() const
{
    return {
        m_block.Get_Pos().x - Tile_Size / 2.0f,
        m_block.Get_Pos().y - Tile_Size,
        Tile_Size,
        Tile_Size};
}
