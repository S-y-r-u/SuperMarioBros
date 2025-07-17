#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Button.h"



class Menu {
private:
    Button playButton;
    Button settingBtn;
    Button infoButton ;
    Button quitButton ;
    Texture MenuTexture;
public:
	Menu() ;
    void Draw();
    int Update();
    ~Menu();
};
