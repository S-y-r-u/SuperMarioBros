#include "Item/Item.h"

Item::Item(Vector2 pos)
    : animation_(nullptr),
      pos_(pos),
      appear_animation(1),
      is_delete(0) {}

Vector2 Item::Get_Pos() const { return pos_; }

void Item::Set_Pos(Vector2 pos) { pos_ = pos; }

Rectangle Item::Get_Source_Rec() const { return animation_.Get_Current_Rec(); }

Rectangle Item::Get_Draw_Rec() const { return {pos_.x - animation_.Get_Current_Rec().width * scale_screen / 2.0f, pos_.y - animation_.Get_Current_Rec().height * scale_screen, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen}; }

bool Item::Is_Appear_Animation() const { return appear_animation; }

bool Item::Get_Is_Delete() const { return is_delete; }

void Item::Draw_()
{
    Rectangle dest_rec = {pos_.x, pos_.y, animation_.Get_Current_Rec().width * scale_screen, animation_.Get_Current_Rec().height * scale_screen};
    DrawTexturePro(animation_.Get_Sprite().sprite, animation_.Get_Current_Rec(), dest_rec, {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);
}
