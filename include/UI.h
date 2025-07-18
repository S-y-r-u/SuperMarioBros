#pragma once
#include"Constants.h"
#include"raylib.h"
#include "Menu.h"
#include "GameManager.h"
#include "ChoosingStageState.h"
#include "Constants.h"
#include "resource_dir.h"
#include "SoundManager.h"
class UI {
public:
	UI();
	void Process();
private:
	int Program_state ;
	Font font;
};
