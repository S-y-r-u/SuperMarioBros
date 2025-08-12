#pragma once
#include "Flag.h"

class Flag_Castle : public Flag
{
private:
    Vector2 ini_pos;
public:
    Flag_Castle(Vector2 pos);
    void Update(float dt) override;
};
