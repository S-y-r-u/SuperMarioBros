#include "GameManager/Concrete_Pause.h"
#include "Constants.h"
#include <iostream>

Non_Pause::Non_Pause(PauseManager &pm)
    : pause_manager(pm),
      pause_button(1100, 80, 50, CircleButton::PAUSE)
{
}

void Non_Pause::Draw_()
{
    pause_button.Draw();
}

int Non_Pause::Update_()
{
    if (pause_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Pause_Menu_State());
        // Chuyển sang trạng thái pause menu
    }
    return PauseSelect::Pause_None_Select;
}

Pause_Menu::Pause_Menu(PauseManager &pm)
    : pause_manager(pm),
      resume_button("Resume", (Screen_w - 200) / 2, 290, 200, 50),
      restart_button("Restart", (Screen_w - 200) / 2, 390, 200, 50),
      exit_button("Exit", (Screen_w - 200) / 2, 490, 200, 50),
      save_button("Save", (Screen_w - 200) / 2, 590, 200, 50)
{
    pause_background = LoadTexture("Menu/Pause_Menu.png");
}

Pause_Menu::~Pause_Menu()
{
    UnloadTexture(pause_background);
}

void Pause_Menu::Draw_()
{
    Rectangle destRect = {(Screen_w - (float)pause_background.width * 0.6f) / 2.0f, (Screen_h - (float)pause_background.height * 0.6f) / 2.0f, (float)pause_background.width * 0.6f, (float)pause_background.height * 0.6f};
    DrawTexturePro(pause_background, {0, 0, (float)pause_background.width, (float)pause_background.height}, destRect, {0, 0}, 0.0f, WHITE);
    resume_button.Draw();
    restart_button.Draw();
    exit_button.Draw();
    save_button.Draw();
}

int Pause_Menu::Update_()
{
    if (resume_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Non_Pause_State());
        return PauseSelect::Pause_Resume_Select;
        // Trở về trạng thái không pause
    }
    if (save_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Non_Pause_State());
        return PauseSelect::Pause_Save_Select;
    }
    if (restart_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Non_Pause_State());
        return PauseSelect::Pause_Restart_Select;
        // Trở về trạng thái không pause và yêu cầu restart
    }
    if (exit_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Exit_Confirmation_State());
        return PauseSelect::Pause_None_Select;
        // Chuyển sang trạng thái xác nhận thoát
    }
    if (save_button.Update()){
        
    }
    return PauseSelect::Pause_None_Select;
    // Không có lựa chọn nào được thực hiện
}

Exit_Confirmation::Exit_Confirmation(PauseManager &pm)
    : pause_manager(pm),
      yes_button(720, 440, 30, CircleButton::YES),
      no_button(560, 440, 30, CircleButton::NO)
{
    exit_background = LoadTexture("Menu/Exit_Confirmation.png");
}

Exit_Confirmation::~Exit_Confirmation()
{
    UnloadTexture(exit_background);
}

void Exit_Confirmation::Draw_()
{
    Rectangle destRect = {(Screen_w - (float)exit_background.width * 0.6f) / 2.0f, (Screen_h - (float)exit_background.height * 0.6f) / 2.0f, (float)exit_background.width * 0.6f, (float)exit_background.height * 0.6f};
    DrawTexturePro(exit_background, {0, 0, (float)exit_background.width, (float)exit_background.height}, destRect, {0, 0}, 0.0f, WHITE);
    yes_button.Draw();
    no_button.Draw();
}

int Exit_Confirmation::Update_()
{
    if (yes_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Non_Pause_State());
        return PauseSelect::Pause_Exit_Select;
        // Trở về trạng thái không pause và yêu cầu thoát
    }
    if (no_button.Update())
    {
        pause_manager.Set_Pause_State(pause_manager.Get_Pause_Menu_State());
        return PauseSelect::Pause_None_Select;
        // Trở về trạng thái pause menu
    }
    return PauseSelect::Pause_None_Select;
    // Không có lựa chọn nào được thực hiện
}