#pragma once

#include <SDL.h>

class Sprite
{
public:

	Sprite(SDL_Texture* texture, SDL_Rect* crop, int x, int y);
	~Sprite();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

	void crop( SDL_Rect* crop );

	SDL_Texture* getTexture();
	SDL_Rect*    getCrop();

private:

	int x = 0;
	int y = 0;

	SDL_Texture* texture     = nullptr;
	SDL_Rect*    textureCrop = nullptr;
	
};

