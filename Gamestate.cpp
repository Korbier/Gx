#include "Gamestate.h"

#include "Window.h"
#include "GameHandler.h"

void Gamestate::initialize(Window* window, GameHandler* gamehandler)
{
	this->window = window;
	this->gameHandler = gamehandler;
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
}

void Gamestate::render()
{
}
