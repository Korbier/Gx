#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"

#include "boost/log/trivial.hpp"

#include "GameHandler.h"
#include "Display.h"
#include "Gamestate.h"
#include "Timer.h"
#include "TextureManager.h"

void Game::initialize()
{

	this->running = false;

	this->gHandler = new GameHandler();
	this->display = new Display();
	this->state = new Gamestate();
	this->textureManager = new TextureManager();
	
	BOOST_LOG_TRIVIAL(info) << "Game start";

}

void Game::finalize()
{
	
	this->textureManager->finalize();
	this->state->finalize();
	this->display->finalize();

	IMG_Quit();
	SDL_Quit();

	delete this->state;
	delete this->display;
	delete this->gHandler;

	BOOST_LOG_TRIVIAL(info) << "Game end";

}

void Game::run()
{

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	this->gHandler->initialize(this->display, this);

	BOOST_LOG_TRIVIAL(info) << "Initializing display";

	if (!this->display->initialize("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
		BOOST_LOG_TRIVIAL(info) << "An error occured during display init";
	}

	BOOST_LOG_TRIVIAL(info) << "Initializing texture manager\n";
	this->textureManager->initialize(this->display);

	BOOST_LOG_TRIVIAL(info) << "Initializing gamestate";
	this->state->initialize(this->display, this->gHandler);

	BOOST_LOG_TRIVIAL(info) << "Entering game loop";
	this->next_time = SDL_GetTicks() + TICKS_PER_FRAME;
	this->running   = true;

	//game loop
	while (this->isRunning()) {
		
		this->input();

		this->state->update();
		this->render();

		SDL_Delay(this->time_left());
		next_time += TICKS_PER_FRAME;

	}
	
	this->finalize();

}

void Game::stop() 
{
	BOOST_LOG_TRIVIAL(info) << "Game interruption requested";
	this->running = false;
}

bool Game::isRunning()
{
	return this->running;
}

int Game::getFramerate()
{
	return FRAMES_PER_SECOND;
}

TextureManager* Game::getTextureManager()
{
	return this->textureManager;
}

void Game::input()
{
	
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT:
			this->stop();
		}

		this->state->input(&event);

	}

}

void Game::render()
{
	SDL_RenderClear(this->display->getRenderer());
	this->state->render();
	SDL_RenderPresent(this->display->getRenderer());
}

Uint32 Game::time_left()
{
	Uint32 now;

	now = SDL_GetTicks();
	if (this->next_time <= now)
		return 0;
	else
		return next_time - now;
}
