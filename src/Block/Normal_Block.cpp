#include "Block/Normal_Block.h"

Normal_Block::Normal_Block(Block &block)
    : m_block(block), delta_time(0.0f), elapse_(0), change_state(0)
{
    before_pos = m_block.Get_Pos();
    rec_ = Item_Sprite::Brown_Brick::type_2;
}

void Normal_Block::Draw_()
{
    Rectangle dest_rec = {
        m_block.Get_Pos().x,
        m_block.Get_Pos().y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};
    DrawTexturePro(
        m_block.Get_Sprite().sprite,
        rec_,
        dest_rec,
        {dest_rec.width / 2.0f, dest_rec.height},
        0.0f,
        WHITE);
}

void Normal_Block::Update_()
{
    Elapse_();
    Change_State();
}

void Normal_Block::On_Hit(std::vector<Item*> &item, Character &character)
{
    if (m_block.Get_Item_Count() > 0)
    {
        Spawn_Item::Item_Spawn(m_block.Get_Type_Item(), item, m_block.Get_Pos(), character);
        m_block.Decrease_Item();
        elapse_ = true;
        delta_time = 0.0f;
    }
    change_state = 1;
}

void Normal_Block::Elapse_()
{
    if (!elapse_)
        return;

    delta_time += 0.14f;
    float delta_y = -Push_Height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
    Vector2 tmp = m_block.Get_Pos();
    tmp.y = before_pos.y + delta_y;
    m_block.Set_Pos(tmp);

    float t_max = 2 * Push_Height / Physics::gravity_;
    if (delta_time >= t_max)
    {
        elapse_ = false;
        m_block.Set_Pos(before_pos);
    }
}

void Normal_Block::Change_State()
{
    if (change_state)
        m_block.Set_State(m_block.GetBreakableState());
}

Rectangle Normal_Block::Get_Draw_Rec() const { return {m_block.Get_Pos().x - rec_.width * scale_screen / 2.0f, m_block.Get_Pos().y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }

bool Normal_Block::Get_Elapse() { return elapse_; }