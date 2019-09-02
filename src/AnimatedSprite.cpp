#include "AnimatedSprite.h"

#include "boost/log/trivial.hpp"

AnimatedSprite::AnimatedSprite(SDL_Texture* texture, SDL_Rect* crop, int x, int y, int size):Sprite(texture, crop, x, y, size)
{
	this->timer = new Timer();
	this->timer->start();
}

void AnimatedSprite::update()
{

	if (this->timer->getTicks() > 30) {

		this->getCrop()->x += 32;
		if (this->getCrop()->x > 32 * 3) {
			this->getCrop()->x = 0;
		}

		this->timer->stop();
		this->timer->start();

	}
	
	Sprite::update();
}

void AnimatedSprite::play()
{
	this->timer->unpause();
}

void AnimatedSprite::pause()
{
	this->timer->pause();
}
