#include "Block/Block.h"
#include "Block/Abstract_Block_State.h"
#include "Block/Question_Block.h"
#include "Block/Normal_Block.h"
#include "Block/Breakable_Block.h"
#include "Block/Unbreakable_Block.h"

Block::Block(Vector2 pos, int item_count, const std::string &type_item, const std::string &type_block)
    : pos_(pos),
      item_count_(item_count),
      type_item_(type_item)
{
    question_state_ = new Question_Block(*this);
    normal_state_ = new Normal_Block(*this);
    unbreakable_state_ = new Unbreakable_Block(*this);
    break_state_ = new Breakable_BLock(*this);
    if (type_block == "question")
        current_state_ = question_state_;
    else if (type_block == "normal")
        current_state_ = normal_state_;
    else if (type_block == "unbreakable")
        current_state_ = unbreakable_state_;
}

Block::~Block()
{
    delete question_state_;
    delete normal_state_;
    delete break_state_;
    delete unbreakable_state_;
    current_state_ = nullptr;
}

void Block::Draw_()
{
    current_state_->Draw_();
}

void Block::Update_()
{
    current_state_->Update_();
}

void Block::On_Hit(std::vector<Item *> &item, Player &player, PlayerInformation &info)
{
    current_state_->On_Hit(item, player, info);
}

bool Block::Kill_Player(Player &player)
{
    return current_state_->Kill_Player(player);
}

void Block::Set_State(A_Block_State *new_state)
{
    current_state_ = new_state;
}

Vector2 Block::Get_Pos() const
{
    return pos_;
}

void Block::Set_Pos(Vector2 pos)
{
    pos_ = pos;
}

int Block::Get_Item_Count() const
{
    return item_count_;
}

Rectangle Block::Get_Draw_Rec() const { return current_state_->Get_Draw_Rec(); }

bool Block::Get_Elapse() const { return current_state_->Get_Elapse(); }

bool Block::Get_Is_Delete() const { return current_state_->Get_Is_Delete(); }

std::string Block::Get_Type_Item() const { return type_item_; }

void Block::Decrease_Item()
{
    item_count_--;
}

A_Block_State *Block::GetQuestionState() const
{
    return question_state_;
}

A_Block_State *Block::GetNormalState() const
{
    return normal_state_;
}

A_Block_State *Block::GetUnbreakableState() const
{
    return unbreakable_state_;
}

A_Block_State *Block::GetBreakableState() const
{
    return break_state_;
}