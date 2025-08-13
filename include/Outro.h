#pragma once
#include "GameManager/I_Stage.h"
#include "GameManager/Animation.h"
#include "Constants.h"
#include <raylib.h>

class Outro : public I_Stage
{
public:
    Outro(Player_Mode mode);
    ~Outro();

    void Draw() override;
    void Run() override;
    bool Change_State() override;

private:
    Animation animation;
    float radius;
    const float Max_Radius = 200.0f;
    Player_Mode player_mode;

    Shader shader_;
    int uResolution_;
    int uCenter_;
    int uRadius_;
};
