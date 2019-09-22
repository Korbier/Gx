#include "Game.h"

#include <sstream>

#include "SDL.h"
#include "SDL_image.h"

#include "boost/log/trivial.hpp"

#include "GameHandler.h"
#include "Display.h"
#include "gamestate/Gamestate.h"
#include "utils/Timer.h"
#include "display/texture/TextureManager.h"
#include "input/InputBuffer.h"

Game::Game()
{
	this->running        = false;
	this->display        = new Display("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT, false, false);
	this->textureManager = new TextureManager(this->display);
	this->gHandler       = new GameHandler(this->display, this);
	this->inputBuffer    = {};
	this->gStateManager  = {};
}

Game::~Game()
{
	
	delete this->textureManager;
	delete this->display;
	delete this->gHandler;

	BOOST_LOG_TRIVIAL(info) << "Game end";

}

void Game::run()
{

	BOOST_LOG_TRIVIAL(info) << "Game start";

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	this->display->show();
	this->gStateManager.push(new Gamestate(this->display, this->gHandler));
	
	BOOST_LOG_TRIVIAL(info) << "Entering game loop";
	Uint32 lastMeasure = SDL_GetTicks();
	this->running     = true;

	int fpsTime = 0;
	int fps = 0;

	//game loop
	while (this->isRunning()) {
		
		this->input();

		Uint32 currentMeasure = SDL_GetTicks();

		this->gStateManager.update(this->inputBuffer, currentMeasure - lastMeasure);
		this->render();

		fps++;
		fpsTime += (currentMeasure - lastMeasure);
		if (fpsTime >= 1000) {
			std::stringstream title;
			title << "MyGame (fps: " << fps << ")";
			this->display->setWindowTitle(title.str());
			fps = 0;
			fpsTime = 0;
		}
			 
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
		case SDL_KEYDOWN: this->inputBuffer.press(event.key.keysym.scancode); break;
		case SDL_KEYUP:   this->inputBuffer.release(event.key.keysym.scancode); break;
		case SDL_QUIT:    this->stop(); break;
		case SDL_MOUSEBUTTONDOWN: 
			switch (event.button.button) {
				case SDL_BUTTON_LEFT: this->inputBuffer.pressMouseLeft(); break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
				case SDL_BUTTON_LEFT: this->inputBuffer.releaseMouseLeft(); break;
			}
			break;
		}

	}

	this->inputBuffer.updateMouse();

}

void Game::render()
{
	SDL_RenderClear(this->display->getRenderer());
	this->gStateManager.render();
	SDL_RenderPresent(this->display->getRenderer());
}
