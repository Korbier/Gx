#pragma once

#include <SDL.h>

class Texture
{
public:

	Texture(SDL_Texture* texture);
	Texture(SDL_Texture* texture, SDL_Rect crop);
	~Texture();

	void crop( SDL_Rect crop );

	SDL_Texture* getTexture();
	SDL_Rect     getCrop();
	SDL_Rect* getPCrop();

private:

	SDL_Texture* texture = nullptr;
	SDL_Rect     textureCrop;
	
};

