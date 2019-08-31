#include "Game.h"

void Game::initialize()
{
	this->running = false;
	this->window = new Window();
	this->state = new Gamestate();
}

void Game::finalize()
{
	
	this->state->finalize();
	this->window->finalize();

	SDL_Quit();

	delete this->state;
	delete this->window;

}

void Game::run()
{

	if (!this->window->initialize("hello !!!", SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
	}

	this->state->initialize(this->window);

	//game loop
	while (this->isRunning()) {

	}
	
	this->finalize();

}

void Game::stop() 
{
	this->running = false;
}

bool Game::isRunning()
{
	return this->running;
}
