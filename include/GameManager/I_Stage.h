#pragma once
#include <raylib.h>
#include "sprite.h"
#include "Constants.h"

class I_Stage
{
public:
    virtual ~I_Stage() = default;
    virtual void Draw() = 0;
    virtual void Run() = 0;
    virtual bool Change_State() = 0;

    virtual json to_json() const { return json(); };
    virtual void from_json(const json& j) {};
};