#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"

#define ENABLE_TRACE
#include "Trace.h"

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

	this->capTimer = new Timer();

	TRACE("Game start");

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

	TRACE("Game end");

}

void Game::run()
{

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	this->gHandler->initialize(this);

	TRACE("Initializing display");

	if (!this->display->initialize("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
		ERROR("An error occured during display init");
	}
	else {
		TRACE("Display initialized");
	}

	TRACE("Initializing texture manager");
	this->textureManager->initialize(this->display);
	TRACE("Texture manager initialized");

	TRACE("Initializing gamestate");
	this->state->initialize(this->display, this->gHandler);
	TRACE("Gamestate initialized");

	TRACE("Executing game loop");
	this->running = true;

	//game loop
	while (this->isRunning()) {

		this->capTimer->start();

		this->state->input();

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
	TRACE("Game interruption requested");
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

void Game::render()
{
	SDL_RenderClear(this->display->getRenderer());
	this->state->render();
	SDL_RenderPresent(this->display->getRenderer());
}
