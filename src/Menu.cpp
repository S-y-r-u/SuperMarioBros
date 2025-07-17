#include "Menu.h"
#include "raylib.h"



Menu::Menu() : playButton("Play", 274, 500),settingBtn("Setting", 774, 500),  infoButton("Info", 274, 600),quitButton("Quit", 774, 600)  {
	// Constructor can be used to initialize any member variables if needed
    MenuTexture = LoadTexture("Menu.jpg");
}



void Menu::Draw() {
    DrawTexture(MenuTexture, 0, 0, WHITE);
    playButton.Draw();
    settingBtn.Draw();
    infoButton.Draw();
    quitButton.Draw();

}

int Menu::Update() {
    if (playButton.Update()) {
        std::cout << "PLAY\n";
        return choosingStageState;
    }
    if (settingBtn.Update()) {
        return settingState;
    }
    if (infoButton.Update()) {
        // return infoState;
    }
    if (quitButton.Update()) {
        // return quitState;
    }
    return menuState;
}

Menu::~Menu() {}
