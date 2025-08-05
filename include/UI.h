#pragma once
#include"Constants.h"
#include"raylib.h"
#include "Menu/Menu.h"
#include "Menu/GameManager.h"
#include "Menu/ChoosingStageState.h"
#include "Constants.h"
#include "resource_dir.h"
#include "Menu/SoundManager.h"
#include "Menu/SettingState.h"
#include "Menu/CursorManager.h"

class UI {
public:
	UI();
	void Process();
private:
	int Program_state ;
	Font font;
	bool type_cursor = 0;
};
