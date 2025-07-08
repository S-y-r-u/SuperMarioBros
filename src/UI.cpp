
#include "UI.h"
#include "Menu.h"
#include "GameManager.h"
#include "resource_dir.h"
//#include "SettingScreen.h"

UI::UI() {
    SearchAndSetResourceDir("resources");
}

void UI::Process() {
    InitWindow(Screen_w, Screen_h, "Mario Game");
    SetTargetFPS(60);


    auto menu = std::make_unique<Menu>();
    //auto setting = std::make_unique<SettingScreen>();
    auto gameManager = std::make_unique<GameManager>();

    menu->Init();
    //setting->Init();
    gameManager->Init();

    int Program_state = menuState;

    while (!WindowShouldClose()) {
        if (Program_state == menuState) {
            Program_state = menu->HandleEvent();
        }
        else if (Program_state == settingState) {
            //setting->Update(Program_state);
        }
        else if (Program_state == gameManagerState) {
            gameManager->Update(Program_state);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (Program_state == menuState) {
            menu->Draw();
        }
        else if (Program_state == settingState) {
            //setting->Draw();
        }
        else if (Program_state == gameManagerState) {
            gameManager->Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    UnloadFont(font);

    //menu->Unload();
    //setting->Unload();
    //gameManager->Unload();
}