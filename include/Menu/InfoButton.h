#pragma once
#include "constants.h"
#include "Menu/Button.h"
#include "Menu/Menu.h"

class InfoButton{
    private:
        Texture2D* MenuTexture;
        CircleButton BackButton;
    public:
        InfoButton();
        void Draw();
        int Update();
        ~InfoButton();
};
