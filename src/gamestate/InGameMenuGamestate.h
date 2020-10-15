#pragma once

#include "gamestate/MenuGamestate.h"

class InGameMenuGameState : public MenuGamestate
{

public:
	InGameMenuGameState(Display* display, GameHandler* gamehandler);
	~InGameMenuGameState();

	void onReturnPressed();
	void render();
};