#include "Game.h"

#define ENABLE_TRACE
#include "Trace.h"

#include "GameHandler.h"
#include "Window.h"
#include "Gamestate.h"

void Game::initialize()
{
	this->running = false;

	this->gHandler = new GameHandler();
	this->window = new Window();
	this->state = new Gamestate();

	TRACE("Game start");

}

void Game::finalize()
{
	
	this->state->finalize();
	this->window->finalize();

	SDL_Quit();

	delete this->state;
	delete this->window;

	TRACE("Game end");

}

void Game::run()
{
	this->gHandler->initialize(this);

	if (this->window->initialize("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
		TRACE("Window initialized");		
	}
	else {
		ERROR("An error occured during window init");
	}

	this->state->initialize(this->window, this->gHandler);
	TRACE("Gamestate initialized");

	TRACE("Executing game loop");
	this->running = true;

	//game loop
	while (this->isRunning()) {
		this->state->input();
		this->state->update();
		this->render();
	}
	
	this->finalize();

}

void Game::stop() 
{
	TRACE("Game interruption requested");
	this->running = false;
}

bool Game::isRunning()
{
	return this->running;
}

void Game::render()
{
	SDL_RenderClear(this->window->getRenderer());
	this->state->render();
	SDL_RenderPresent(this->window->getRenderer());
}
