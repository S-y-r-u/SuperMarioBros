#pragma once
#include "raylib.h"
#include "Constants.h"
#include "PlayerInformation.h"
#include "Player.h"

class I_Win_Animation_Manager
{
public:
    I_Win_Animation_Manager() = default;
    virtual ~I_Win_Animation_Manager() = default;

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;

    virtual void Enter_Win_Animation() = 0;
    virtual bool Check_Win_Animation() = 0;

    virtual bool End_Animation() = 0;

};