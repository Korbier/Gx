#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedSprite.h"
#include "Entity.h"
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
	this->tank = new Entity(new AnimatedSprite(this->gameHandler->getTexture(TANK_SPRITESHEET), 50), 0, 0);
	this->tank->setXVelocity( 300 );
	this->tank->setYVelocity(300);
	this->tank->getSprite()->addFrame(0, 0, 32, 32);
	this->tank->getSprite()->addFrame(32, 0, 32, 32);
	this->tank->getSprite()->addFrame(64, 0, 32, 32);
	this->tank->getSprite()->addFrame(96, 0, 32, 32);
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

	this->tank->getSprite()->animate();

}

void Gamestate::render()
{
	SDL_Rect* dst = new SDL_Rect();
	dst->x = (int) this->tank->getX();
	dst->y = (int) this->tank->getY();
	dst->w = dst->h = 64;
	this->gameHandler->render(this->tank->getSprite(), dst );
	delete dst;
}
