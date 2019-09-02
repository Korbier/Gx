#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedSprite.h"

#define RESOURCE_TANK "resources/tank_move_002.png"

void Gamestate::initialize(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;
	this->crop = new SDL_Rect();
	this->crop->h = 32;
	this->crop->w = 32;
	this->crop->x = 0;
	this->crop->y = 0;
	this->tank = new AnimatedSprite(gamehandler->getTexture(RESOURCE_TANK), this->crop, 0, 100, 64);
}

void Gamestate::finalize()
{
	delete this->tank;
}

void Gamestate::input(SDL_Event* event)
{

	BOOST_LOG_TRIVIAL(info) << "Event type : " << event->type ;
	BOOST_LOG_TRIVIAL(info) << "ScanCode : " << event->key.keysym.sym;

	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_LEFT) {
		this->tank->pause();
	}

	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RIGHT) {
		this->tank->play();
	}

}

void Gamestate::update()
{
	this->tank->setX( this->tank->getX() + 2 );
	
	if (this->tank->getX() > 640) {
		this->tank->setX(0);
	}

	this->tank->update();

}

void Gamestate::render()
{
	this->gameHandler->render( this->tank );
}
