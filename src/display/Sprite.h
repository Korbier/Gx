#pragma once

#include <SDL.h>
#include "display/Hitbox.h"
#include "display/texture/AnimatedTexture.h"

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
	Hitbox getHitbox();
	SDL_FPoint getHitboxCenter();
	float getHitboxRadius();

	float getAngle();
	void rotate(float angle);
	void setAngle(float angle);

	virtual AnimatedTexture* getTexture();
	virtual bool isRenderable();
		
protected:

	Hitbox hitbox;

private:
	
	SDL_FPoint position;
	SDL_FPoint velocity;
	SDL_Point size;

	float angle;

	AnimatedTexture* texture;

};

