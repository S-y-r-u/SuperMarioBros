#include "Block/Abstract_Block_State.h"

Rectangle A_Block_State::Get_Source_Rec() const { return rec_; }

bool A_Block_State::Get_Is_Delete() const { return false; }