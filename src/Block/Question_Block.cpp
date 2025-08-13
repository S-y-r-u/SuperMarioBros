#include "Block/Question_Block.h"

Question_Block::Question_Block(Block &block)
    : A_Block_State(),
      m_block(block),
      velocity_y(0.0f),
      elapse_(false)
{
    before_pos = m_block.Get_Pos();
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Question_Brick::question_, 1 / 6.0f);
}

void Question_Block::Draw_()
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
}

void Question_Block::Animation_()
{
    animation_.Update(GetFrameTime());
}

void Question_Block::Update_()
{
    Animation_();
    Elapse_();
    Change_State();
}

void Question_Block::On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info)
{
    if (m_block.Get_Item_Count() > 0)
    {
        m_block.Decrease_Item();
        Spawn_Item::Item_Spawn(m_block.Get_Type_Item(), item, m_block.Get_Pos(), player, info);
        elapse_ = true;
        velocity_y = -Push_Height; // Đẩy lên
    }
    else SoundManager::GetInstance().PlaySoundEffect("bump");
}

void Question_Block::Elapse_()
{
    if (!elapse_)
        return;

    float dt = GetFrameTime();
    velocity_y += Physics::gravity_ * dt;

    Vector2 tmp = m_block.Get_Pos();
    tmp.y += velocity_y * dt;

    if (tmp.y >= before_pos.y)
    {
        tmp.y = before_pos.y;
        velocity_y = 0.0f;
        elapse_ = false;
    }

    m_block.Set_Pos(tmp);
}

void Question_Block::Change_State()
{
    if (m_block.Get_Item_Count() == 0 && !elapse_)
    {
        m_block.Set_State(m_block.GetUnbreakableState());
    }
}

bool Question_Block::Get_Elapse()
{
    return elapse_;
}

Rectangle Question_Block::Get_Draw_Rec() const
{
    return {
        m_block.Get_Pos().x - animation_.Get_Current_Rec().width * scale_screen / 2.0f,
        m_block.Get_Pos().y - animation_.Get_Current_Rec().height * scale_screen,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};
}

// Serialize Question_Block
json Question_Block::to_json() const {
    json j;
    j["elapse"] = elapse_;
    j["before_pos"] = {before_pos.x, before_pos.y};
    j["velocity_y"] = velocity_y;
    j["animation"] = animation_.to_json();
    // Có thể lưu thêm animation nếu muốn
    return j;
}

void Question_Block::from_json(const json& j) {
    elapse_ = j.value("elapse", false);
    before_pos.x = j["before_pos"][0];
    before_pos.y = j["before_pos"][1];
    velocity_y = j.value("velocity_y", 0.0f);
    animation_.from_json(j["animation"]);
    // Có thể đọc thêm animation nếu muốn
}