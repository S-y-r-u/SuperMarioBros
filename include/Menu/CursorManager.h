#pragma once
#include "raylib.h"

class CursorManager
{
public:
    static void Update_();
    static void Set_Cursor(int cursor);
    static int Get_Current_Cursor();

private:
    static int current_cursor;
};
