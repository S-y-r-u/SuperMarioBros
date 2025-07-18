#pragma once
#include "raylib.h"
#include "Constants.h"
#include "Mario.h"
#include <vector>

class Stage {
    private:
        Rectangle source;
        Rectangle dest;
    protected:
        Texture MapTexture;
        int Map[214][15];
        Player* player;
        Camera2D camera = {0};
    public:
        Stage();
        virtual ~Stage();
        void Run();
        void Draw();
};