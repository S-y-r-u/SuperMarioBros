#pragma once
#include "Constants.h"
#include "Button.h" 

class ChoosingStageState {
public:
    ChoosingStageState();
    void Draw();
    int Update();
    Difficulty GetSelectedDifficulty() const;
    ~ChoosingStageState();
private:
    Texture MenuTexture;    
    Difficulty selectedDifficulty = Difficulty::Easy;
    
    Button* easyButton;
    Button* mediumButton;
    Button* hardButton;
};
