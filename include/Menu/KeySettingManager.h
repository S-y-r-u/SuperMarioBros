#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>
#include <vector>

// ==================== Action enum ====================
enum class Action {
    LEFT,
    RIGHT,
    UP,
    FIREBALL,
    SWAP_TO_MARIO,
    SWAP_TO_LUIGI
};

// ==================== KeySettingManager ====================
class KeySettingManager {
private:
    static std::unordered_map<Action, int> bindings;
    std::vector<std::pair<Action, std::string>> actionList;

    bool isEditing;
    Action editingAction;
    const float startY = 250 ;
    const float rowHeight = 50;
    const float col1X = 700;
    const float col2X = 900;

public:
    KeySettingManager();

    void update();
    void draw();

    // ====== static để Player gọi ======
    static void initializeDefaults();
    static void setKey(Action action, int key);
    static int getKey(Action action);
    static std::string keyToString(int key);
};
