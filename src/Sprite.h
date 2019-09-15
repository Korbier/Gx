#pragma once

#include "SDL.h"

class Texture;
class AnimatedTexture;

class Sprite
{
public:
	
	Sprite(AnimatedTexture* texture, SDL_FPoint position, SDL_Point size );
	~Sprite();

	SDL_FPoint getVelocity();
	void setVelocity(SDL_FPoint velocity);

	SDL_FPoint getPosition();
	void setPosition(SDL_FPoint position);
	void move(SDL_FPoint position);

	SDL_Point getSize();

	float getAngle();
	void rotate(float angle);
	void setAngle(float angle);

	AnimatedTexture* getTexture();
		
private:
	
	SDL_FPoint position;
	SDL_FPoint velocity;
	SDL_Point size;

	float angle;

	AnimatedTexture* texture;

};

