#include "Block/Fire_Block.h"

Fire_Block::Fire_Block(Vector2 pos) : fire_animation(&Win_Animation::win_animation_, Fire_Block_Animation::fire_block_, 1 / 8.0f), pos(pos) {}

void Fire_Block::Update()
{
    fire_animation.Update(GetFrameTime());
}

void Fire_Block::Draw()
{
    Rectangle src_rec = fire_animation.Get_Current_Rec();
    Rectangle des_rec = {pos.x, pos.y, src_rec.width * scale_screen, src_rec.height * scale_screen};
    DrawTexturePro(fire_animation.Get_Sprite().sprite, src_rec, des_rec, {des_rec.width / 2.0f, des_rec.height}, 0.0f, WHITE);
}

Vector2 Fire_Block::Get_Pos()
{
    return pos;
}