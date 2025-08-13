#include "Block/Normal_Block.h"

Normal_Block::Normal_Block(Block &block)
    : A_Block_State(),
      m_block(block),
      elapse_(false),
      change_state(false),
      velocity_y(0.0f)
{
    before_pos = m_block.Get_Pos();
    animation_ = Animation(&Item_Sprite::item_, Item_Sprite::Brown_Brick::type_2);
    is_break = (m_block.Get_Type_Item() == "");
}

void Normal_Block::Draw_()
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

void Normal_Block::Update_()
{
    Elapse_();
    Change_State();
    animation_.Update(GetFrameTime());
}

void Normal_Block::On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info)
{
    if (m_block.Get_Item_Count() > 0)
    {
        Spawn_Item::Item_Spawn(m_block.Get_Type_Item(), item, m_block.Get_Pos(), player, info);
        m_block.Decrease_Item();
        elapse_ = true;
        velocity_y = -Push_Height; // đẩy lên
        if (m_block.Get_Item_Count() == 0)
        {
            change_state = true;
            return;
        }
    }
    else if (m_block.Get_Item_Count() == 0 &&
             (player.get_form() == PlayerForm::Small || player.get_form() == PlayerForm::Invincible))
    {
        elapse_ = true;
        velocity_y = -Push_Height; // đẩy lên
        SoundManager::GetInstance().PlaySoundEffect("bump");
    }
    else
    {
        SoundManager::GetInstance().PlaySoundEffect("breakblock");
        change_state = true;
    }
}

void Normal_Block::Elapse_()
{
    if (!elapse_)
        return;

    float dt = GetFrameTime();
    velocity_y += Physics::gravity_ * dt;

    Vector2 tmp = m_block.Get_Pos();
    tmp.y += velocity_y * dt;

    // Nếu đã về lại vị trí cũ (hoặc vượt quá)
    if (tmp.y >= before_pos.y)
    {
        tmp.y = before_pos.y;
        velocity_y = 0.0f;
        elapse_ = false;
    }

    m_block.Set_Pos(tmp);
}

void Normal_Block::Change_State()
{
    if (change_state && is_break)
    {
        m_block.Set_State(m_block.GetBreakableState());
    }
    else if (change_state && !is_break && !elapse_)
    {
        m_block.Set_State(m_block.GetUnbreakableState());
    }
}

Rectangle Normal_Block::Get_Draw_Rec() const
{
    return {
        m_block.Get_Pos().x - animation_.Get_Current_Rec().width * scale_screen / 2.0f,
        m_block.Get_Pos().y - animation_.Get_Current_Rec().height * scale_screen,
        animation_.Get_Current_Rec().width * scale_screen,
        animation_.Get_Current_Rec().height * scale_screen};
}

bool Normal_Block::Get_Elapse()
{
    return elapse_ || change_state;
}

// Demo: Serialize Normal_Block
json Normal_Block::to_json() const {
    json j;
    j["elapse"] = elapse_;
    j["change_state"] = change_state;
    j["is_break"] = is_break;
    j["before_pos"] = {before_pos.x, before_pos.y};
    j["velocity_y"] = velocity_y;
    j["animation"] = animation_.to_json();
    // Có thể lưu thêm animation nếu muốn
    return j;
}

void Normal_Block::from_json(const json& j) {
    elapse_ = j.value("elapse", false);
    change_state = j.value("change_state", false);
    is_break = j.value("is_break", false);
    before_pos.x = j["before_pos"][0];
    before_pos.y = j["before_pos"][1];
    velocity_y = j.value("velocity_y", 0.0f);
    animation_.from_json(j["animation"]);
    // Có thể đọc thêm animation nếu muốn
}