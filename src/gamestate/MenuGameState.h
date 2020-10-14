#pragma once

#include <SDL_ttf.h>

#include "boost/log/trivial.hpp"

#include "gamestate/Gamestate.h"
#include "display/text/Text.h"

class MenuGameState: public Gamestate
{

public:
	MenuGameState(Display* display, GameHandler* gamehandler);
	~MenuGameState();

	void initialize();
	void update(InputBuffer input, Uint32 delta);
	void render();

private:
	TTF_Font* font;

	int selection = 0;

	Text* textRun;
	Text* textOptions;
	Text* textQuit;

};

