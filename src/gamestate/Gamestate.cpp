#include "Gamestate.h"

Gamestate::Gamestate(Display* display, GameHandler* gamehandler)
{
	this->display = display;
	this->gameHandler = gamehandler;
	this->target = new SDL_Rect();
	this->target->w = this->target->h = TILE_SIZE;
}

Gamestate::~Gamestate()
{
}
