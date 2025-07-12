#pragma once
#include "Constants.h"

class ChoosingStageState {
public:
    void Init();
    void Draw();
    int Update();
    Difficulty GetSelectedDifficulty() const;
private:
    Difficulty selectedDifficulty = Difficulty::Easy;
};
