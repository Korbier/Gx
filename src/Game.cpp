#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"

#include "boost/log/trivial.hpp"

#include "GameHandler.h"
#include "Display.h"
#include "Gamestate.h"
#include "Timer.h"
#include "TextureManager.h"
#include "InputBuffer.h"

Game::Game()
{
	this->running        = false;
	this->display        = new Display("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	this->textureManager = new TextureManager(this->display);
	this->gHandler       = new GameHandler(this->display, this);
	this->state          = new Gamestate(this->display, this->gHandler);
	this->inputBuffer = new InputBuffer();
}

Game::~Game()
{
	
	delete this->inputBuffer;
	delete this->textureManager;
	delete this->display;
	delete this->state;
	delete this->gHandler;

	BOOST_LOG_TRIVIAL(info) << "Game end";

}

void Game::run()
{

	BOOST_LOG_TRIVIAL(info) << "Game start";

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	this->display->show();
	this->state->initialize();
	
	BOOST_LOG_TRIVIAL(info) << "Entering game loop";
	Uint32 lastMeasure = SDL_GetTicks();
	this->running     = true;

	//game loop
	while (this->isRunning()) {
		
		this->input();

		Uint32 currentMeasure = SDL_GetTicks();

		this->state->update( this->inputBuffer, currentMeasure - lastMeasure );
		this->render();

		lastMeasure = currentMeasure;
		
		SDL_Delay(1);

	}

	IMG_Quit();
	SDL_Quit();

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
	
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_KEYDOWN: this->inputBuffer->press(event.key.keysym.scancode); break;
		case SDL_KEYUP:   this->inputBuffer->release(event.key.keysym.scancode); break;
		case SDL_QUIT:    this->stop(); break;
		}

	}

}

void Game::render()
{
	SDL_RenderClear(this->display->getRenderer());
	this->state->render();
	SDL_RenderPresent(this->display->getRenderer());
}
