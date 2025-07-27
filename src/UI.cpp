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

    SoundManager::GetInstance().LoadSounds();
    SoundManager::GetInstance().LoadMusic();
    SoundManager::GetInstance().PlayMusic("background", true);

    Menu *menu = new Menu();
    ChoosingStageState *choosingStage = new ChoosingStageState();
    GameManager *gameManager = new GameManager();

    Program_state = menuState;

    gameManager->Load_Texture();

    while (!WindowShouldClose())
    {
        if (Program_state == menuState)
        {
            Program_state = menu->Update();
        }
        else if (Program_state == choosingStageState) {
            SoundManager::GetInstance().Update();
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

        EndDrawing();
    }

    gameManager->Unload_Texture();
    SoundManager::GetInstance().UnloadAll();
    delete menu;
    delete choosingStage;
    delete gameManager;

    CloseAudioDevice();
    CloseWindow();
}
