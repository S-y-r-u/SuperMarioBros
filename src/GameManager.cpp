#include "GameManager.h"
#include "raylib.h"

constexpr int NUM_MONITORED_KEYS = 16;
constexpr int MONITORED_KEYS[NUM_MONITORED_KEYS] = {
    KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN,
    KEY_A, KEY_S, KEY_D, KEY_W,
    KEY_SPACE, KEY_X, KEY_C, KEY_Z,
    KEY_LEFT_CONTROL, KEY_LEFT_SHIFT, KEY_P, KEY_ESCAPE
};

GameManager::GameManager() : stage(nullptr) {}

GameManager::~GameManager() {
    delete stage;
}

void GameManager::Init() {
    if (stage) delete stage;
    stage = nullptr; // Replace with actual stage initialization
}

void GameManager::SetDifficulty(Difficulty diff) {
    difficulty = diff;

    // Delete the old stage if it exists
    if (stage) {
        delete stage;
        stage = nullptr;
    }

    // Create a new stage based on the selected difficulty
    switch (difficulty) {
    case Difficulty::Easy:
        stage = new EasyMap(); // Replace with your actual Easy stage class
        break;
    case Difficulty::Medium:
        stage = new MediumMap(); // Replace with your actual Medium stage class
        break;
    case Difficulty::Hard:
        stage = new HardMap(); // Replace with your actual Hard stage class
        break;
    default:
        stage = nullptr;
        break;
    }
}

int GameManager::Update() {
    UpdateKeyStates();
    if (IsKeyPressed(KEY_ESCAPE)) {
        return menuState;
    }
	return gameManagerState; // Continue in game manager state
}

void GameManager::UpdateKeyStates() {
    keyStates.clear();
    for (int i = 0; i < NUM_MONITORED_KEYS; ++i) {
        int keyCode = MONITORED_KEYS[i];
        bool isPressed = IsKeyDown(keyCode);
        keyStates.emplace_back(keyCode, isPressed);
    }
}

void GameManager::Draw() {
	stage->Draw();  // Assuming Stage has a Draw method
    // Draw stage and game elements here
}
