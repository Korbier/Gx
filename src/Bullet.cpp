#include "Bullet.h"

#include "AnimatedTexture.h"

Bullet::Bullet(AnimatedTexture* texture, SDL_FPoint position, SDL_Point size):Sprite(nullptr, position, size)
{
	this->setTexture(0, texture);
}

void Bullet::setTexture(int state, AnimatedTexture* texture) {
	this->textures[state] = texture;
}

AnimatedTexture* Bullet::getTexture()
{
	return this->textures[this->state];
}

void Bullet::setState(int state) {
	this->state = state;
}