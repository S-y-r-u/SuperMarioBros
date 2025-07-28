#include "UI.h"

UI::UI()
{
    SearchAndSetResourceDir("resources");
}

void UI::Process()
{
    InitWindow(Screen_w, Screen_h, "Mario Game");
    SetTargetFPS(60);
    InitAudioDevice();

    MenuImages::GetInstance().Load();
    SoundManager::GetInstance().LoadSounds();
    SoundManager::GetInstance().LoadMusic();
    
    // Bắt đầu với menu music
    SoundManager::GetInstance().PlayMusic("MenuMusic", true);

    Menu *menu = new Menu();
    ChoosingStageState *choosingStage = new ChoosingStageState();
    GameManager *gameManager = new GameManager();

    Program_state = menuState;
    int previousState = menuState;  // Track previous state để quản lý music

    gameManager->Load_Texture();

    while (!WindowShouldClose())
    {
        // Quản lý music khi state thay đổi
        if (Program_state != previousState)
        {
            // Stop current music
            SoundManager::GetInstance().StopMusic();
            
            // Play appropriate music for new state
            if (Program_state == menuState || Program_state == settingState)
            {
                SoundManager::GetInstance().PlayMusic("MenuMusic", true);
            }
            else if (Program_state == choosingStageState)
            {
                SoundManager::GetInstance().PlayMusic("playingMusic", true);
            }
            // else if (Program_state == gameManagerState)
            // {
            //     SoundManager::GetInstance().PlayMusic("playingMusic", true);
            // }
            
            previousState = Program_state;
        }
        SoundManager::GetInstance().Update();
        // Update logic
        if (Program_state == menuState)
        {
            Program_state = menu->Update();
        }
        else if (Program_state == choosingStageState) 
        {
            int nextState = choosingStage->Update();
            if (nextState == gameManagerState)
            {
                gameManager->SetDifficulty(choosingStage->GetSelectedDifficulty());
            }
            Program_state = nextState;
        }
        else if (Program_state == gameManagerState)
        {
            Program_state = gameManager->Update();
        }
        else if (Program_state == settingState)
        {
            // Xử lý setting state (nếu có)
            // Program_state = settingMenu->Update();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (Program_state == menuState)
        {
            menu->Draw();
        }
        else if (Program_state == choosingStageState)
        {
            choosingStage->Draw();
        }
        else if (Program_state == gameManagerState)
        {
            gameManager->Draw();
        }
        else if (Program_state == settingState)
        {
            // settingMenu->Draw();
        }

        EndDrawing();
    }

    // Cleanup
    SoundManager::GetInstance().StopMusic();
    gameManager->Unload_Texture();
    SoundManager::GetInstance().UnloadAll();
    MenuImages::GetInstance().Unload();
    delete menu;
    delete choosingStage;
    delete gameManager;

    CloseAudioDevice();
    CloseWindow();
}