#pragma once

#include <utility>
#include "SDL.h"

class Camera
{
public:

	void setPosition(int x, int y);
	void setSize(int width, int height);

	void move(float x, float y);
	SDL_Point getPosition();
	SDL_Point getSize();

	void toCameraView(SDL_Point * point);
	void toCameraView(SDL_Rect * rect);

private:
	SDL_Point position;
	SDL_Point size;
};
