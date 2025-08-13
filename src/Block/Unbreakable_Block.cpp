#include "Block/Unbreakable_Block.h"

Unbreakable_Block::Unbreakable_Block(Block &m_block)
    : A_Block_State(),
    m_block(m_block)
{
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Brown_Brick::type_1);
    if (m_block.Get_Type_Item() == "rotating_bar")
        m_rotating_bar = new RotatingBar({m_block.Get_Pos().x, m_block.Get_Pos().y - animation_.Get_Current_Rec().height * scale_screen / 2.0f});
    else
        m_rotating_bar = nullptr;
}

Unbreakable_Block::~Unbreakable_Block()
{
    if (m_rotating_bar)
        delete m_rotating_bar;
    m_rotating_bar = nullptr;
}

void Unbreakable_Block::Draw_()
{
    Rectangle dest_rec = {
        m_block.Get_Pos().x,
        m_block.Get_Pos().y,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(
        animation_.Get_Sprite().sprite,
        animation_.Get_Current_Rec(),
        dest_rec,
        {dest_rec.width / 2.0f, dest_rec.height},
        0.0f,
        WHITE);

    if (m_rotating_bar)
        m_rotating_bar->Draw();
}

void Unbreakable_Block::Update_()
{
    if (m_rotating_bar)
        m_rotating_bar->Update(GetFrameTime());
}

bool Unbreakable_Block::Get_Elapse() { return false; }

Rectangle Unbreakable_Block::Get_Draw_Rec() const
{
    return {m_block.Get_Pos().x - animation_.Get_Current_Rec().width * scale_screen / 2.0f, m_block.Get_Pos().y - animation_.Get_Current_Rec().height * scale_screen, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
}

void Unbreakable_Block::On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info)
{
    // Unbreakable block does not respond to hits
    SoundManager::GetInstance().PlaySoundEffect("bump");
}

bool Unbreakable_Block::Kill_Player(Player &player)
{
    if (m_rotating_bar)
        return m_rotating_bar->CheckCollision(player.get_draw_rec());
    return false;
}