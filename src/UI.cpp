#include "UI.h"
#include "Menu.h"
#include "GameManager.h"
#include "ChoosingStageState.h"
#include "Constants.h"
#include "resource_dir.h"
//#include "SettingScreen.h"



UI::UI() {
    SearchAndSetResourceDir("resources");
}

void UI::Process() {
    InitWindow(Screen_w, Screen_h, "Mario Game");
    SetTargetFPS(60);

    Menu* menu = new Menu();
    ChoosingStageState* choosingStage = new ChoosingStageState();
    GameManager* gameManager = new GameManager();

    menu->Init();
    choosingStage->Init();
    gameManager->Init();

    int Program_state = menuState;

    while (!WindowShouldClose()) {
        if (Program_state == menuState) {
            Program_state = menu->Update();
        }
        else if (Program_state == choosingStageState) {
            int nextState = choosingStage->Update();
            if (nextState == gameManagerState) {
                gameManager->SetDifficulty(choosingStage->GetSelectedDifficulty());
            }
            Program_state = nextState;
        }
        else if (Program_state == gameManagerState) {
            Program_state = gameManager->Update();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (Program_state == menuState) {
            menu->Draw();
        }
        else if (Program_state == choosingStageState) {
            choosingStage->Draw();
        }
        else if (Program_state == gameManagerState) {
            gameManager->Draw();
        }

        EndDrawing();
    }
    delete menu;
    delete choosingStage;
    delete gameManager;

    CloseWindow();
}
