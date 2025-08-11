#pragma once
#include "Flag.h"

class Flag_Pole : public Flag
{
public:
    Flag_Pole(Vector2 pos);
    void Update(float deltaTime) override;
};