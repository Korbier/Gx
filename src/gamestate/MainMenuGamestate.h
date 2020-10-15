#pragma once

#include "gamestate/MenuGameState.h"
#include "gamestate/LevelGameState.h"

class MainMenuGamestate : public MenuGamestate
{

public:
	MainMenuGamestate(Display* display, GameHandler* gamehandler);
	~MainMenuGamestate();

	void onReturnPressed();
	void render();

};