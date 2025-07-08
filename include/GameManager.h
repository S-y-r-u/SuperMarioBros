#pragma once
#include "raylib.h"
#include "Constants.h"
#include <vector>

class Stage; // Forward declaration

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
