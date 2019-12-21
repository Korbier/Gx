#include "BulletDescriptor.h"

BulletDescriptor::BulletDescriptor(AnimatedTexture* fireTexture, AnimatedTexture* explosionTexture)
{
	this->fireTexture = fireTexture;
	this->fireTexture->addFrame(0, 0, 32, 32);
	this->explosionTexture = explosionTexture;
	this->explosionTexture->addFrame(0, 0, 32, 32);
	this->initialVelocity = { 600, 600 };
}

AnimatedTexture* BulletDescriptor::getFireTexture()
{
	return this->fireTexture;
}

AnimatedTexture* BulletDescriptor::getExplosionTexture()
{
	return this->explosionTexture;
}

void BulletDescriptor::setInitialVelocity(SDL_Point velocity)
{
	this->initialVelocity = velocity;
}

SDL_Point BulletDescriptor::getInitialVelocity()
{
	return this->initialVelocity;
}

int BulletDescriptor::getSize()
{
	return this->size;
}

void BulletDescriptor::setSize(int size)
{
	this->size = size;
}
