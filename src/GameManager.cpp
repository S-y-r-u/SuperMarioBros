#include "GameManager.h"

constexpr int MONITORED_KEYS[NUM_MONITORED_KEYS] = {
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_W,
    KEY_SPACE,
    KEY_X,
    KEY_C,
    KEY_Z,
    KEY_LEFT_CONTROL,
    KEY_LEFT_SHIFT,
    KEY_P,
    KEY_ESCAPE
};

GameManager::GameManager() : stage(nullptr) {}

GameManager::~GameManager() {
    delete stage;
}

void GameManager::Init() {
    // Initialize stage or other game resources
    stage = nullptr; // Replace with actual stage initialization
}

void GameManager::Update(int& state) {
    // Update game logic
	UpdateKeyStates();
	if (IsKeyPressed(KEY_ESCAPE)) {
		state = menuState; // Return to menu state on ESC key press
	}
    //State->update(keyStates);
    
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
    DrawText("Game Running...", 400, 300, 32, RED);
	//Stage->Draw(); // Assuming Stage has a Draw method
    // Draw stage and game elements here
}


