#pragma once
#include "Pause_State.h"
#include "Menu/Button.h"
#include "PauseManager.h"

class Non_Pause : public I_Pause_State
{
private:
    CircleButton pause_button;
    PauseManager& pause_manager;
public:
    Non_Pause(PauseManager& pm);
    ~Non_Pause();
    int Update_() override; // Cập nhật trạng thái pause
    void Draw_() override;   // Vẽ giao diện pause
};

class Pause_Menu : public I_Pause_State
{
private:
    RecButton resume_button;
    RecButton restart_button;
    RecButton exit_button;
    RecButton save_button;
    Texture2D pause_background;
    PauseManager& pause_manager;
public:
    Pause_Menu(PauseManager& pm);
    ~Pause_Menu();
    int Update_() override; // Cập nhật trạng thái pause
    void Draw_() override;   // Vẽ giao diện pause
};

class Exit_Confirmation : public I_Pause_State
{
private:
    CircleButton yes_button;
    CircleButton no_button;
    Texture2D exit_background;
    PauseManager& pause_manager;
public:
    Exit_Confirmation(PauseManager& pm);
    ~Exit_Confirmation();
    int Update_() override;
    void Draw_() override;   // Vẽ giao diện xác nhận thoát
};
