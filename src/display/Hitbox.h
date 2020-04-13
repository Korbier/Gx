#pragma once

#include <SDL.h>

class Hitbox
{
public:
	SDL_FPoint getPosition();
	SDL_Point getSize();
	void setPosition(SDL_FPoint position);
	void setSize(SDL_Point size);
private:
	SDL_FPoint position;
	SDL_Point  size;

};

