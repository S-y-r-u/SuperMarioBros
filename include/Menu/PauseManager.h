#pragma once
#include "Button.h"
#include "Pause_State.h"

// Quản lý trạng thái pause
enum PauseState
{
    Pause_None_State = 0,
    Pause_Menu_State,
    Pause_Exit_Confirmation_State
};

// Quản lý lựa chọn trong pause menu
enum PauseSelect
{
    Pause_None_Select = 0,
    Pause_Resume_Select,
    Pause_Restart_Select,
    Pause_Exit_Select
};

class PauseManager
{
private:
    I_Pause_State *current_state;
    I_Pause_State *non_pause_state;
    I_Pause_State *pause_menu_state;
    I_Pause_State *exit_confirmation_state;

public:
    PauseManager();
    ~PauseManager();
    void Set_Pause_State(I_Pause_State *state);
    int Get_Pause_State() const;
    int Get_Pause_Select() const;
    void Draw();
    I_Pause_State *Get_Current_State() const;
    I_Pause_State *Get_Non_Pause_State() const;
    I_Pause_State *Get_Pause_Menu_State() const;
    I_Pause_State *Get_Exit_Confirmation_State() const;
};