#include "Block/Question_Block.h"

Question_Block::Question_Block(Block &block)
    : m_block(block), m_rec(Item_Sprite::Question_Brick::question_), frame_(0), type_(0), delta_time(0.0f), elapse_(0)
{
    before_pos = m_block.Get_Pos();
    rec_ = m_rec[type_];
}

void Question_Block::Draw_()
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

void Question_Block::Animation_()
{
    frame_++;
    if (frame_ >= 12)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0;
    }
    rec_ = m_rec[type_];
}

void Question_Block::Update_()
{
    Animation_();
    Elapse_();
    Change_State();
}

void Question_Block::On_Hit(std::vector<Item *> &item, Player &player)
{
    if (m_block.Get_Item_Count() > 0)
    {
        m_block.Decrease_Item();
        Spawn_Item::Item_Spawn(m_block.Get_Type_Item(), item, m_block.Get_Pos(), player);
        elapse_ = true;
        delta_time = 0.0f;
    }
}

void Question_Block::Elapse_()
{
    if (!elapse_)
        return;

    delta_time += 0.14f;
    float delta_y = -Push_Height * delta_time + 0.5f * delta_time * delta_time * Physics::gravity_;
    Vector2 tmp = m_block.Get_Pos();
    tmp.y = before_pos.y + delta_y;
    m_block.Set_Pos(tmp);
}

void Question_Block::Change_State()
{
    float t_max = 2 * Push_Height / Physics::gravity_;

    if (m_block.Get_Item_Count() == 0 && elapse_ && delta_time >= t_max)
    {
        elapse_ = false;
        m_block.Set_Pos(before_pos);
        m_block.Set_State(m_block.GetUnbreakableState());
    }
    else if (elapse_ && delta_time >= t_max)
    {
        elapse_ = false;
        m_block.Set_Pos(before_pos);
    }
}

bool Question_Block::Get_Elapse() { return elapse_; }

Rectangle Question_Block::Get_Draw_Rec() const { return {m_block.Get_Pos().x - rec_.width * scale_screen / 2.0f, m_block.Get_Pos().y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }
