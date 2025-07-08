#pragma once
#include"Constants.h"
#include"raylib.h"
class UI {
public:
	UI();
	void Process();
private:
	int Program_state = -1;
	Font font;
};
