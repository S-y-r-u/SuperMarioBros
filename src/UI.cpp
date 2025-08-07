#include "UI.h"

UI::UI()
{
    SearchAndSetResourceDir("resources");
}

void UI::Process()
{
    InitWindow(Screen_w, Screen_h, "Mario Game");
    SetTargetFPS(120);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitAudioDevice();

    MenuImages::GetInstance().Load();
    SoundManager::GetInstance().LoadSounds();
    SoundManager::GetInstance().LoadMusic();

    // Bắt đầu với menu music
    SoundManager::GetInstance().PlayMusic("MenuMusic", true);

    Menu *menu = new Menu();
    ChoosingStageState *choosingStage = new ChoosingStageState();
    GameManager *gameManager = new GameManager();
    SettingState *settingMenu = new SettingState();
    ChoosingCharacter* choosingCharacter = new ChoosingCharacter();


    Program_state = menuState;
    int previousState = menuState; // Track previous state để quản lý music

    gameManager->Load_Texture();

    while (!WindowShouldClose())
    {
        type_cursor = 0;
        // Quản lý music khi state thay đổi
        if (Program_state != previousState)
        {
            // Stop current music
            if (Program_state == gameManagerState || previousState == gameManagerState) 
            {
                SoundManager::GetInstance().StopMusic();
                if (Program_state == menuState)
                {
                    SoundManager::GetInstance().PlayMusic("MenuMusic", true);
                }
                else if (Program_state == gameManagerState)
                {
                    SoundManager::GetInstance().PlayMusic("playingMusic", true);
                }
            }
            previousState = Program_state;
        }
        SoundManager::GetInstance().Update();
        // Update logic
        if (Program_state == menuState)
        {
            Program_state = menu->Update();
            if (Program_state == gameManagerState){
                gameManager->SetDifficulty(choosingStage->GetSelectedDifficulty());
                // gameManager->SetCharacter(choosingCharacter->GetCharacter());
            }
        }
        else if (Program_state == choosingStageState)
        {
            Program_state = choosingStage->Update();;
        }
        else if (Program_state == gameManagerState)
        {
            Program_state = gameManager->Update();
        }
        else if (Program_state == settingState)
        {
            Program_state = settingMenu->Update();
        }
        else if (Program_state == choosingCharacterState)
        {
            Program_state = choosingCharacter->Update();
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
            settingMenu->Draw();
        }
        else if (Program_state == choosingCharacterState)
        {
            choosingCharacter->Draw();
        }

        EndDrawing();
        CursorManager::Update_(); // Cập nhật con trỏ mỗi frame
    }

    // Cleanup
    SoundManager::GetInstance().StopMusic();
    gameManager->Unload_Texture();
    SoundManager::GetInstance().UnloadAll();
    MenuImages::GetInstance().Unload();
    delete menu;
    delete choosingStage;
    delete gameManager;
    delete settingMenu;
    delete choosingCharacter;

    CloseAudioDevice();
    CloseWindow();
}