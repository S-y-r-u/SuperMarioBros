#pragma once
#include "Menu/Menu.h"
#include "GameManager/GameManager.h"
#include <fstream>
#include "Constants.h"

class ContinueState {
public:
    ContinueState() = default;
    virtual ~ContinueState() = default;

    int Update();
};