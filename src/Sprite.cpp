#include "Sprite.h"

#include "AnimatedTexture.h"

Sprite::Sprite(AnimatedTexture* texture, SDL_FPoint position, SDL_Point size )
{
	this->texture = texture;
	this->setPosition( position );
	this->setVelocity({ 0, 0});
	this->size = size;
}

Sprite::~Sprite()
{
	delete this->texture;
}

SDL_FPoint Sprite::getVelocity()
{
	return this->velocity;
}

void Sprite::setVelocity(SDL_FPoint velocity)
{
	this->velocity = velocity;
}

SDL_FPoint Sprite::getPosition()
{
	return this->position;
}

void Sprite::move(SDL_FPoint position)
{
	SDL_FPoint current = this->getPosition();
	this->setPosition({ current.x + position.x, current.y + position.y });
}

SDL_Point Sprite::getSize()
{
	return this->size;
}

void Sprite::setPosition(SDL_FPoint position)
{
	this->position = position;
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
	return this->texture;
}

