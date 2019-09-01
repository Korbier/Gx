#include "Gamestate.h"

#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"

#define ENABLE_TRACE
#include "Trace.h"

#define RESOURCE_TANK "resources/tank_001.png"

void Gamestate::initialize(Display* display, GameHandler* gamehandler)
{
	this->display = display;
	this->gameHandler = gamehandler;
	this->texture = gamehandler->getTexture(RESOURCE_TANK );
}

void Gamestate::finalize()
{
	//SDL_DestroyTexture( this->texture );
	SDL_FreeSurface( this->image );
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

}

void Gamestate::render()
{
	SDL_RenderCopy(this->display->getRenderer(), this->texture, NULL, NULL);
}
