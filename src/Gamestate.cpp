#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"

#define RESOURCE_TANK "resources/tank_001.png"

void Gamestate::initialize(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;
	this->texture     = gamehandler->getTexture( RESOURCE_TANK );
	this->texture2    = gamehandler->getTexture(RESOURCE_TANK);
	this->dst = new SDL_Rect();
}

void Gamestate::finalize()
{
}

void Gamestate::input(SDL_Event* event)
{
	
}

void Gamestate::update()
{
	this->dst->w = 32;
	this->dst->h = 32;
	this->dst->x = 100;
	this->dst->y = 100;
}

void Gamestate::render()
{
	this->gameHandler->render( this->texture2, nullptr, nullptr);
	this->gameHandler->render( this->texture, nullptr, this->dst);
}
