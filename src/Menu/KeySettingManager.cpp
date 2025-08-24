#include "Menu/KeySettingManager.h"
#include <iostream>

// Định nghĩa static map
std::unordered_map<Action, int> KeySettingManager::bindings;

// ====== Constructor ======
KeySettingManager::KeySettingManager() {
    initializeDefaults();
    actionList = {
        {Action::LEFT, "Move Left"},
        {Action::RIGHT, "Move Right"},
        {Action::UP, "Jump / Up"},
        {Action::FIREBALL, "Throw Fireball"},
        {Action::SWAP_TO_MARIO, "Swap to Mario"},
        {Action::SWAP_TO_LUIGI, "Swap to Luigi"}
    };
    isEditing = false;
    editingAction = Action::LEFT;
}

// ====== Static methods ======
void KeySettingManager::initializeDefaults() {
    bindings = {
        {Action::LEFT, KEY_A},
        {Action::RIGHT, KEY_D},
        {Action::UP, KEY_W},
        {Action::FIREBALL, KEY_F},
        {Action::SWAP_TO_MARIO, KEY_ONE},
        {Action::SWAP_TO_LUIGI, KEY_TWO}
    };
}

void KeySettingManager::setKey(Action action, int key) {
    // Không cho trùng phím
    if (key != 0) {
        for (auto &pair : bindings) {
            if (pair.second == key && pair.first != action) {
                std::cout << "Conflict: key already used!\n";
                return;
            }
        }
    }
    bindings[action] = key;
}

int KeySettingManager::getKey(Action action) {
    return bindings[action];
}

// ====== Update UI ======
void KeySettingManager::update() {
    if (isEditing) {
        int newKey = GetKeyPressed();
        if (newKey != 0 && newKey != KEY_BACKSPACE) {
            setKey(editingAction, newKey);
            isEditing = false;
        } else if (IsKeyPressed(KEY_BACKSPACE)) {
            setKey(editingAction, 0);
            isEditing = false;
        }
    } else {
        Vector2 mouse = GetMousePosition();

        for (int i = 0; i < actionList.size(); i++) {
            Rectangle keyBox = {col2X, startY + i * rowHeight, 200, 40};
            if (CheckCollisionPointRec(mouse, keyBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                isEditing = true;
                editingAction = actionList[i].first;
            }
        }
    }
}

// ====== Draw UI ======
void KeySettingManager::draw() {

    for (int i = 0; i < actionList.size(); i++) {
        float rowY = startY + i * rowHeight;

        DrawText(actionList[i].second.c_str(), col1X, rowY + 10, 20, BLACK);

        Rectangle keyBox = {col2X, rowY, 200, 40};
        Color boxColor = (isEditing && editingAction == actionList[i].first) ? ORANGE : LIGHTGRAY;
        DrawRectangleRec(keyBox, boxColor);
        DrawRectangleLinesEx(keyBox, 2, BLACK);

        std::string keyName = keyToString(bindings[actionList[i].first]);
        Vector2 size = MeasureTextEx(GetFontDefault(), keyName.c_str(), 20, 1);
        DrawText(keyName.c_str(), keyBox.x + (keyBox.width - size.x) / 2, keyBox.y + 10, 20, BLACK);
    }
}

// ====== Key to string ======
std::string KeySettingManager::keyToString(int key) {
    if (key == 0) return "";

    if (key >= KEY_A && key <= KEY_Z) return std::string(1, 'A' + (key - KEY_A));
    if (key >= KEY_ZERO && key <= KEY_NINE) return std::string(1, '0' + (key - KEY_ZERO));
    if (key >= KEY_F1 && key <= KEY_F12) return "F" + std::to_string(1 + (key - KEY_F1));

    switch (key) {
        case KEY_SPACE: return "Space";
        case KEY_ESCAPE: return "Escape";
        case KEY_ENTER: return "Enter";
        case KEY_TAB: return "Tab";
        case KEY_BACKSPACE: return "Backspace";
        case KEY_INSERT: return "Insert";
        case KEY_DELETE: return "Delete";
        case KEY_RIGHT: return "Right Arrow";
        case KEY_LEFT: return "Left Arrow";
        case KEY_DOWN: return "Down Arrow";
        case KEY_UP: return "Up Arrow";
        case KEY_LEFT_SHIFT: return "Left Shift";
        case KEY_RIGHT_SHIFT: return "Right Shift";
        case KEY_LEFT_CONTROL: return "Left Ctrl";
        case KEY_RIGHT_CONTROL: return "Right Ctrl";
        case KEY_LEFT_ALT: return "Left Alt";
        case KEY_RIGHT_ALT: return "Right Alt";
        default: return "Key " + std::to_string(key);
    }
}
