#include "Unbreakable_Block.h"

Unbreakable_Block::Unbreakable_Block(Block &m_block)
    : m_block(m_block)
{
    rec_ = Item_Sprite::Brown_Brick::type_1;
}

void Unbreakable_Block::Draw_()
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

void Unbreakable_Block::Update_() {}

void Unbreakable_Block::On_Hit(std::vector<Item *> &item, Character &character) {}

bool Unbreakable_Block::Get_Elapse() { return false; }
Rectangle Unbreakable_Block::Get_Draw_Rec() const { return {m_block.Get_Pos().x - rec_.width * scale_screen / 2.0f, m_block.Get_Pos().y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }