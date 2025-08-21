#pragma once
#include "GameManager/I_Stage.h"
#include "GameManager/Animation.h"
#include "Constants.h"
#include "Mario.h"
#include "Luigi.h"
#include <raylib.h>

class Outro_Manager : public I_Stage
{
public:
    Outro_Manager(Player *&player);
    ~Outro_Manager();

    void Draw() override;
    void Run() override;
    bool Change_State() override;

private:
    Animation animation;
    float radius;
    const float Max_Radius = 200.0f;
    Player *&player;
    float frame_timer;

    Shader shader_;
    int uResolution_;
    int uCenter_;
    int uRadius_;
};
