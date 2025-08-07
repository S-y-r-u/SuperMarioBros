#pragma once
#include "Constants.h"
#include "Menu/Button.h" 
#include "Menu/Menu.h"

class ChoosingCharacter {
public:
    ChoosingCharacter();
    void Draw();
    int Update();
    int  GetCharacter() const;
    ~ChoosingCharacter();

private:
    Texture* MenuTexture;    
    int selectedCharacter = 1;
    
    CircleButton backButton;        // Nút back tròn
    RecButton* marioButton;
    RecButton* luigiButton;
    RecButton* multiplayerButton;
};