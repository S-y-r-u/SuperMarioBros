#pragma once
#include "raylib.h"

class I_Pause_State
{
public:
    virtual int Update_()  = 0; // Cập nhật trạng thái pause
    virtual void Draw_() = 0;
};