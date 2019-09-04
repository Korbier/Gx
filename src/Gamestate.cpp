#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedSprite.h"

void Gamestate::initialize(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;
	this->tank        = new AnimatedSprite(gamehandler->getTexture( TANK_SPRITESHEET ), 100, 100, 50);
	this->tank->addFrame(0,  0, 32, 32);
	this->tank->addFrame(32, 0, 32, 32);
	this->tank->addFrame(64, 0, 32, 32);
	this->tank->addFrame(96, 0, 32, 32);
}

void Gamestate::finalize()
{
	delete this->tank;
}

void Gamestate::input(SDL_Event* event)
{

	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_LEFT) {
		this->tank->setDelay(this->tank->getDelay() - 10);
		BOOST_LOG_TRIVIAL(info) << "New delay : " << tank->getDelay();
	}

	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_RIGHT) {
		this->tank->setDelay(this->tank->getDelay() + 10);
		BOOST_LOG_TRIVIAL(info) << "New delay : " << tank->getDelay();
	}

}

void Gamestate::update()
{
	this->tank->setX( this->tank->getX() + (TANK_SPEED / this->gameHandler->getFramerate() ) );
	
	if (this->tank->getX() > 640) {
		this->tank->setX(0);
	}

	this->tank->animate();

}

void Gamestate::render()
{
	SDL_Rect* dst = new SDL_Rect();
	dst->x = this->tank->getX();
	dst->y = this->tank->getY();
	dst->w = dst->h = 64;
	this->gameHandler->render( this->tank, dst );
	delete dst;
}
