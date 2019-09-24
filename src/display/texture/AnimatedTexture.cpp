#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(SDL_Texture* texture, float delay):Texture(texture)
{
	this->delay = delay;
	this->timer.start();
}

AnimatedTexture::AnimatedTexture(SDL_Texture* texture) :AnimatedTexture(texture, 0.0) {}

AnimatedTexture::~AnimatedTexture()
{
	//TODO Delete animation frames
}

void AnimatedTexture::addFrame(int x, int y, int w, int h)
{
	SDL_Rect frame;
	frame.x = x;
	frame.y = y;
	frame.w = w;
	frame.h = h;
	this->frames.push_back(frame);

	if ( this->frames.size() == 1) {
		this->crop(frame);
	}
}

void AnimatedTexture::setDelay(float delay)
{
	this->delay = delay;
}

float AnimatedTexture::getDelay()
{
	return this->delay;
}

void AnimatedTexture::animate()
{

	if ( this->timer.getTicks() > this->getDelay()) {

		this->index++;

		if (this->index >= this->frames.size()) {
			this->index = 0;
		}

		this->crop(this->frames.at(this->index));
		this->timer.stop();
		this->timer.start();
	}
	
}

void AnimatedTexture::play()
{
	this->timer.unpause();
}

void AnimatedTexture::pause()
{
	this->timer.pause();
}
