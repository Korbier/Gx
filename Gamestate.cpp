#include "Gamestate.h"

#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"

#define ENABLE_TRACE
#include "Trace.h"

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

void Gamestate::input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		this->gameHandler->stop();
	}

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
	SDL_RenderCopy(this->display->getRenderer(), this->texture2, NULL, NULL);
	SDL_RenderCopy(this->display->getRenderer(), this->texture, NULL, this->dst);
}
