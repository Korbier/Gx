#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_Rect* crop, int x, int y)
{	
	this->texture     = texture;
	this->textureCrop = crop;
	this->x = x;
	this->y = y;	
}

Sprite::~Sprite()
{
}

int Sprite::getX()
{
	return this->x;
}

int Sprite::getY()
{
	return this->y;
}

void Sprite::setX(int x)
{
	this->x = x;
}

void Sprite::setY(int y)
{
	this->y = y;
}

void Sprite::crop(SDL_Rect* crop)
{
	this->textureCrop = crop;
}

SDL_Texture* Sprite::getTexture()
{
	return this->texture;
}

SDL_Rect* Sprite::getCrop()
{
	return this->textureCrop;
}

