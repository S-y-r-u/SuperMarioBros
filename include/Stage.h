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
    public:
        Stage();
        virtual ~Stage();
        void Draw();
};