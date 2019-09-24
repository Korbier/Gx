#pragma once

#include <utility>
#include <SDL.h>

class Camera
{
public:

	void setPosition(SDL_FPoint position);
	void setSize(int width, int height);

	void move(float x, float y);
	SDL_FPoint getPosition();
	SDL_Point getSize();

	void toCameraView(SDL_Point * point);
	void toCameraView(SDL_Rect * rect);

	void toWorldView(SDL_Point* point);

private:
	SDL_FPoint position;
	SDL_Point size;
};
