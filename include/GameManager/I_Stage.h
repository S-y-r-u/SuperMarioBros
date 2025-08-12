#pragma once
#include <raylib.h>

class I_Stage
{
public:
    virtual ~I_Stage() = default;
    virtual void Draw() = 0;
    virtual void Run() = 0;
};