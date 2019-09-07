#include "Sprite.h"

#include "AnimatedTexture.h"

Sprite::Sprite(AnimatedTexture* Texture, float x, float y)
{
	this->Texture = Texture;
	this->moveTo(x, y);
}

Sprite::~Sprite()
{
	delete this->Texture;
}

float Sprite::getXVelocity()
{
	return this->xVelocity;
}

float Sprite::getYVelocity()
{
	return this->yVelocity;
}

void Sprite::setXVelocity(float xVelocity)
{
	this->xVelocity = xVelocity;
}

void Sprite::setYVelocity(float yVelocity) {
	this->yVelocity = yVelocity;
}

float Sprite::getX()
{
	return this->x;
}

float Sprite::getY()
{
	return this->y;
}

void Sprite::move(float x, float y)
{
	this->moveTo(this->x + x, this->y + y);
}

void Sprite::moveTo(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Sprite::getAngle()
{
	return this->angle;
}

void Sprite::rotate(float angle)
{
	this->setAngle(this->angle + angle);
}

void Sprite::setAngle(float angle)
{
	this->angle = angle;
}

AnimatedTexture* Sprite::getTexture()
{
	return this->Texture;
}

