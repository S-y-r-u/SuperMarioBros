#pragma once
#include"Constants.h"
#include"raylib.h"
#include "Menu/Menu.h"
#include "GameManager/GameManager.h"
#include "Menu/ChoosingStageState.h"
#include "Constants.h"
#include "resource_dir.h"
#include "Menu/SoundManager.h"
#include "Menu/SettingState.h"
#include "Menu/CursorManager.h"
#include "Menu/ChoosingCharacter.h"
#include "GameManager/GameOver.h"
#include "GameManager/TimeUp.h"

class UI {
public:
	UI();
	void Process();
private:
	int Program_state ;
	Font font;
};
