#pragma once
#include "Constants.h"
#include "Button.h" 
#include "Menu.h"

class ChoosingStageState {
public:
    ChoosingStageState();
    void Draw();
    int Update();
    Difficulty GetSelectedDifficulty() const;
    ~ChoosingStageState();
    
private:
    Texture* MenuTexture;    
    Difficulty selectedDifficulty = Difficulty::Easy;
    
    CircleButton backButton;        // Nút back tròn
    RecButton* easyButton;
    RecButton* mediumButton;
    RecButton* hardButton;
};