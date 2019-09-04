#include "AnimatedSprite.h"

#include "boost/log/trivial.hpp"

AnimatedSprite::AnimatedSprite(SDL_Texture* texture,int x, int y, Uint32 delay):Sprite(texture, nullptr, x, y)
{
	this->delay = delay;
	this->timer = new Timer();
	this->timer->start();
}

void AnimatedSprite::addFrame(int x, int y, int w, int h)
{
	SDL_Rect* frame = new SDL_Rect();
	frame->x = x;
	frame->y = y;
	frame->w = w;
	frame->h = h;
	this->frames.push_back(frame);

	if ( this->frames.size() == 1) {
		this->crop(frame);
	}
}

void AnimatedSprite::setDelay(Uint32 delay)
{
	this->delay = delay;
}

Uint32 AnimatedSprite::getDelay()
{
	return this->delay;
}

void AnimatedSprite::animate()
{

	if ( this->timer->getTicks() > this->getDelay()) {

		this->index++;

		if (this->index >= this->frames.size()) {
			this->index = 0;
		}

		this->crop(this->frames.at(this->index));
		this->timer->stop();
		this->timer->start();
	}
	
}

void AnimatedSprite::play()
{
	this->timer->unpause();
}

void AnimatedSprite::pause()
{
	this->timer->pause();
}
