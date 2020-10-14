#pragma once

#include "Display.h"
#include "GameHandler.h"
#include "input/InputBuffer.h"

const int TILE_SIZE = 32;
const std::string FONT = "resources/font.TTF";

class Gamestate
{
public:
	
	Gamestate(Display* display, GameHandler* gamehandler);
	~Gamestate();

	virtual void initialize() = 0;
	virtual void update(InputBuffer input, Uint32 delta) = 0;
	virtual void render() = 0;

protected:
	Display* display = nullptr;
	GameHandler* gameHandler = nullptr;
	SDL_Rect* target = nullptr;

};