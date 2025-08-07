#pragma once
#include "Constants.h"
#include "Menu/Button.h" 
#include "Menu/Menu.h"

// Dùng để chọn độ khó, chơi 1 map
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