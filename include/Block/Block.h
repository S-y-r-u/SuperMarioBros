#pragma once
#include <raylib.h>
#include <memory>
#include "Constants.h"
#include "Abstract_Block_State.h"
#include "Item/Spawn_Item.h"

class Block
{
private:
    SpriteSheet sprite_;

    A_Block_State *question_state_;
    A_Block_State *normal_state_;
    A_Block_State *unbreakable_state_;
    A_Block_State *break_state_;

    A_Block_State *current_state_;

    Vector2 pos_;
    int item_count_;
    std::string type_item_;

public:
    Block(Vector2 pos, int item_count, const std::string &type_item, const std::string &type_block);
    ~Block();

    void Update_();
    void Draw_();
    void On_Hit(std::vector<Item *> &item, Character &character);

    void Set_State(A_Block_State *new_state);

    Vector2 Get_Pos() const;
    void Set_Pos(Vector2 pos);
    int Get_Item_Count() const;
    Rectangle Get_Source_Rec() const;
    Rectangle Get_Draw_Rec() const;
    bool Get_Elapse() const;
    bool Get_Is_Delete() const;
    std::string Get_Type_Item() const;
    void Decrease_Item();

    const SpriteSheet &Get_Sprite();

    A_Block_State *GetQuestionState() const;
    A_Block_State *GetNormalState() const;
    A_Block_State *GetUnbreakableState() const;
    A_Block_State *GetBreakableState() const;
};