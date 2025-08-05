#pragma once
#include "raylib.h"

class CursorManager
{
public:
    // Không cần constructor/destructor nữa

    static void Update_();
    static void Set_Cursor(int cursor);
    static int Get_Current_Cursor();

private:
    static int current_cursor;
};
