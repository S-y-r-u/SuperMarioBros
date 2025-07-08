#pragma once
#include "raylib.h"
#include "Constants.h"


class Menu {
private:
    Rectangle playBtn = { 400, 250, 200, 60 };
    Rectangle settingBtn = { 400, 350, 200, 60 };
public:
    void Init();
    void Draw();
    int HandleEvent();
    ~Menu();
};
