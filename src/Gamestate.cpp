#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedTexture.h"
#include "Sprite.h"
#include "InputBuffer.h"


Gamestate::Gamestate(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;

}

Gamestate::~Gamestate()
{
	delete this->tank;
}

void Gamestate::initialize() {
	this->tank = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(TANK_TextureSHEET), 20), 0, 0);
	this->tank->setXVelocity( 300 );
	this->tank->setYVelocity(300);
	this->tank->getTexture()->addFrame(0, 0, 32, 32);
	this->tank->getTexture()->addFrame(32, 0, 32, 32);
	this->tank->getTexture()->addFrame(64, 0, 32, 32);
	this->tank->getTexture()->addFrame(96, 0, 32, 32);
}

void Gamestate::update(InputBuffer* input, Uint32 delta )
{
	
	float xVal = 0;
	float yVal = 0;

	if (input->isPressed(SDL_SCANCODE_RIGHT)) xVal = this->tank->getXVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_LEFT))  xVal = -1 * this->tank->getXVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_UP))    yVal = -1 * this->tank->getYVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_DOWN))  yVal = this->tank->getYVelocity() * (delta / 1000.f);

	this->tank->move(xVal, yVal);
	
	bool animateTank = true;

	if (xVal > 0) {
		if (yVal > 0)      this->tank->setAngle(135.0);
		else if (yVal < 0) this->tank->setAngle(45.0);
		else               this->tank->setAngle(90.0);
	}
	else if (xVal < 0) {
		if (yVal > 0)      this->tank->setAngle(225.0);
		else if (yVal < 0) this->tank->setAngle(315.0);
		else               this->tank->setAngle(270.0);
	}
	else {
		if (yVal > 0)      this->tank->setAngle(180.0);
		else if (yVal < 0) this->tank->setAngle(0.0);
		else {
			animateTank = false;
		}
	}

	if (animateTank) {
		this->tank->getTexture()->animate();
	}

}

void Gamestate::render()
{
	SDL_Rect* dst = new SDL_Rect();
	dst->x = (int) this->tank->getX();
	dst->y = (int) this->tank->getY();
	dst->w = dst->h = 32;
	this->gameHandler->render(this->tank, dst );
	delete dst;
}
