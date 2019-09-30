#pragma once

#include <SDL.h>

#include "display/texture/AnimatedTexture.h"

class BulletDescriptor
{
public:
	BulletDescriptor(AnimatedTexture* fireTexture, AnimatedTexture* explosionTexture);
	
	AnimatedTexture* getFireTexture();
	AnimatedTexture* getExplosionTexture();
	
	void setInitialVelocity(SDL_Point velocity);
	SDL_Point getInitialVelocity();

	int getSize();
	void setSize(int size);

private:
	AnimatedTexture* fireTexture;
	AnimatedTexture* explosionTexture;
	SDL_Point initialVelocity;
	int size = 0;
};

