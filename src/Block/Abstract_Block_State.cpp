#include "Block/Abstract_Block_State.h"

A_Block_State::A_Block_State(SpriteSheet *sprite)
    : animation_(sprite)
{}

bool A_Block_State::Get_Is_Delete() const { return false; }

bool A_Block_State::Kill_Player(Player &player)
{
    return false;
}