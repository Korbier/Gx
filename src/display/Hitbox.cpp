#include "Hitbox.h"

SDL_FPoint Hitbox::getPosition()
{
	return this->position;
}

SDL_Point Hitbox::getSize()
{
	return this->size;
}

void Hitbox::setPosition(SDL_FPoint position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

void Hitbox::setSize(SDL_Point size)
{
	this->size.x = size.x;
	this->size.y = size.y;
}
