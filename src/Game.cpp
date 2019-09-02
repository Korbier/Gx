#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"

#include "boost/log/trivial.hpp"

#include "GameHandler.h"
#include "Display.h"
#include "Gamestate.h"
#include "Timer.h"
#include "TextureManager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void Game::initialize()
{

	this->running = false;

	this->gHandler = new GameHandler();
	this->display = new Display();
	this->state = new Gamestate();
	this->textureManager = new TextureManager();

	this->capTimer = new Timer();

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
	delete this->capTimer;

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
	else {
		BOOST_LOG_TRIVIAL(info) << "Display initialized";
	}

	BOOST_LOG_TRIVIAL(info) << "Initializing texture manager\n";
	this->textureManager->initialize(this->display);
	BOOST_LOG_TRIVIAL(info) << "Texture manager initialized";

	BOOST_LOG_TRIVIAL(info) << "Initializing gamestate";
	this->state->initialize(this->display, this->gHandler);
	BOOST_LOG_TRIVIAL(info) << "Gamestate initialized";

	BOOST_LOG_TRIVIAL(info) << "Executing game loop";
	this->running = true;

	//game loop
	while (this->isRunning()) {

		this->capTimer->start();

		this->input();

		this->state->update();
		this->render();

		int frameTicks = this->capTimer->getTicks();
		if (frameTicks < TICKS_PER_FRAME )
		{
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}

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

TextureManager* Game::getTextureManager()
{
	return this->textureManager;
}

void Game::input()
{
	
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		this->stop();
	}

	this->state->input( &event );

}

void Game::render()
{
	SDL_RenderClear(this->display->getRenderer());
	this->state->render();
	SDL_RenderPresent(this->display->getRenderer());
}
