#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_Rect* crop, int x, int y, int size)
{
	
	this->texture = texture;
	this->textureCrop = crop;
	this->x = x;
	this->y = y;

	this->dstRect = new SDL_Rect();
	this->dstRect->h = size;
	this->dstRect->w = size;

	this->update();

}

Sprite::~Sprite()
{
	delete this->dstRect;
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

SDL_Rect* Sprite::getDstRect()
{
	return this->dstRect;
}

void Sprite::update()
{
	this->dstRect->x = this->getX();
	this->dstRect->y = this->getY();
}
