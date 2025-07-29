#include "Item/Item.h"

Item::Item(Vector2 pos)
    : item_(Item_Sprite::item_), pos_(pos), frame_(0), type_(0), appear_animation(1), is_delete(0) {}

Vector2 Item::Get_Pos() const { return pos_; }

void Item::Set_Pos(Vector2 pos) { pos_ = pos; }

Rectangle Item::Get_Source_Rec() const { return rec_; }

Rectangle Item::Get_Draw_Rec() const { return {pos_.x - rec_.width * scale_screen / 2.0f, pos_.y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }

bool Item::Is_Appear_Animation() const { return appear_animation; }

bool Item::Get_Is_Delete() const { return is_delete; }

void Item::Draw_()
{
    Rectangle dest_rec = {pos_.x, pos_.y, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(item_.sprite, rec_, dest_rec, {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);
}
