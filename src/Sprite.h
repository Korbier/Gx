#pragma once

#include <SDL.h>

class Sprite
{
public:

	Sprite(SDL_Texture* texture);
	Sprite(SDL_Texture* texture, SDL_Rect* crop);
	~Sprite();

	void crop( SDL_Rect* crop );

	SDL_Texture* getTexture();
	SDL_Rect*    getCrop();

private:

	SDL_Texture* texture     = nullptr;
	SDL_Rect*    textureCrop = nullptr;
	
};

