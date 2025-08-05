#include "Menu/CursorManager.h"

int CursorManager::current_cursor = MOUSE_CURSOR_DEFAULT;

void CursorManager::Set_Cursor(int cursor)
{
    if (cursor != current_cursor)
    {
        current_cursor = cursor;
    }
}

int CursorManager::Get_Current_Cursor()
{
    return current_cursor;
}

void CursorManager::Update_()
{
    // Nếu muốn reset về mặc định mỗi frame (tùy bạn)
    SetMouseCursor(current_cursor);
    current_cursor = MOUSE_CURSOR_DEFAULT;
}
