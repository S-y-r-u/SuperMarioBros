#pragma once
#include "EasyMap.h"
#include "MediumMap.h"
#include "HardMap.h"

class GameManager {
public:
    GameManager();
    ~GameManager();

    void Init();
    void Update(int& state);
	void UpdateKeyStates();
    void Draw();

private:
    Stage* stage;
    std::vector<std::pair<int, bool>> keyStates;
};
