#include "Menu/ContinueState.h"
#include <fstream>


int ContinueState::Update() {
    std::ifstream f("save.json");
    if (f.is_open()) {
        f.close();
        std::cout << "oke" << std::endl;
        return ProgramState::gameManagerState; // 1: GameManagerState
    }
    std::cout << "Failed to open save file." << std::endl;
    return ProgramState::menuState; // 0: MenuState
}
