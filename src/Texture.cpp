#include "Texture.h"

Texture::Texture(SDL_Texture* texture):Texture(texture, nullptr) {}

Texture::Texture(SDL_Texture* texture, SDL_Rect* crop)
{	
	this->texture     = texture;
	this->textureCrop = crop;
}

Texture::~Texture()
{
}

void Texture::crop(SDL_Rect* crop)
{
	this->textureCrop = crop;
}

SDL_Texture* Texture::getTexture()
{
	return this->texture;
}

SDL_Rect* Texture::getCrop()
{
	return this->textureCrop;
}

