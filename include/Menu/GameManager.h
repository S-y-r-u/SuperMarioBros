#pragma once
#include "Constants.h"
#include "Stage.h"
#include "EasyMap.h"
#include "MediumMap.h"
#include "HardMap.h"
#include "Sprite.h"

class Stage; // Forward declaration

class GameManager {
public:
    GameManager();
    ~GameManager();

    int Update();
    void Draw();
    void SetDifficulty(Difficulty diff);
    void Load_Texture();
    void Unload_Texture();

private:
    Stage* stage;
    Difficulty difficulty = Difficulty::Easy;
    void UpdateKeyStates();
    std::vector<std::pair<int, bool>> keyStates;
};
