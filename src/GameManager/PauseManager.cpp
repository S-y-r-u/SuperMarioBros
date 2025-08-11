#include "GameManager/PauseManager.h"
#include "GameManager/Concrete_Pause.h"
#include <iostream>

PauseManager::PauseManager()
    : non_pause_state(new Non_Pause(*this)),
      pause_menu_state(new Pause_Menu(*this)),
      exit_confirmation_state(new Exit_Confirmation(*this))
{
    current_state = non_pause_state; // Start with non-pause state
}

PauseManager::~PauseManager()
{
    delete non_pause_state;
    delete pause_menu_state;
    delete exit_confirmation_state;
    current_state = nullptr; 
}

void PauseManager::Set_Pause_State(I_Pause_State *state)
{
    current_state = state;
}

int PauseManager::Get_Pause_State() const
{
    if (current_state == non_pause_state)
        return PauseState::Pause_None_State;
    else if (current_state == pause_menu_state)
        return PauseState::Pause_Menu_State;
    else if (current_state == exit_confirmation_state)
        return PauseState::Pause_Exit_Confirmation_State;
    return PauseState::Pause_None_State; // Default case
}

int PauseManager::Get_Pause_Select() const
{
    return current_state->Update_();
}

void PauseManager::Draw()
{
    if (current_state)
        current_state->Draw_();
}
I_Pause_State *PauseManager::Get_Current_State() const
{
    return current_state;
}

I_Pause_State *PauseManager::Get_Non_Pause_State() const
{
    return non_pause_state;
}

I_Pause_State *PauseManager::Get_Pause_Menu_State() const
{
    return pause_menu_state;
}

I_Pause_State *PauseManager::Get_Exit_Confirmation_State() const
{
    return exit_confirmation_state;
}