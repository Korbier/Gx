#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture):Sprite(texture, nullptr) {}

Sprite::Sprite(SDL_Texture* texture, SDL_Rect* crop)
{	
	this->texture     = texture;
	this->textureCrop = crop;
}

Sprite::~Sprite()
{
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

