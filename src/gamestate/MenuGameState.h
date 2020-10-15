#pragma once

#include <SDL_ttf.h>

#include "boost/log/trivial.hpp"

#include "gamestate/Gamestate.h"
#include "display/text/Text.h"

class MenuGamestate: public Gamestate
{

public:
	MenuGamestate(Display* display, GameHandler* gamehandler);
	~MenuGamestate();

	virtual void initialize();
	virtual void update(InputBuffer input, Uint32 delta);
	virtual void render();

protected:
	
	void addItem(int selector, std::string text);
	virtual void onUpPressed();
	virtual void onDownPressed();
	virtual void onRightPressed();
	virtual void onLeftPressed();
	virtual void onReturnPressed();

	unsigned int getSelection();


private:
	TTF_Font* font;

	unsigned int selection = 0;
	std::map<int, Text*> items;

	bool wasUpPressed   = false;
	bool wasDownPressed = false;
	bool wasRightPressed = false;
	bool wasLeftPressed = false;
	bool wasReturnPressed = false;

	void clearItems();
	void renderItems();
	void enlightSelection();

};

