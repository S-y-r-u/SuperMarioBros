#pragma once
#include "Constants.h"
#include "Menu/Button.h" 
#include "Menu/Menu.h"

class ChoosingCharacter {
public:
    ChoosingCharacter();
    void Draw();
    int Update();
    Player_Mode GetCharacter() const;  // Lấy nhân vật đã chọn
    ~ChoosingCharacter();

private:
    Texture* MenuTexture;    
    Player_Mode selectedCharacter = Player_Mode::MARIO_PLAYER; // Nhân vật được chọn

    CircleButton backButton;        // Nút back tròn
    RecButton* marioButton;
    RecButton* luigiButton;
    RecButton* multiplayerButton;
};