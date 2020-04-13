#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(SDL_Texture* texture, float delay):Texture(texture)
{
	this->delay = delay;
	this->timer.start();
}

AnimatedTexture::AnimatedTexture(SDL_Texture* texture) :AnimatedTexture(texture, 0.0) {}

AnimatedTexture::AnimatedTexture(AnimatedTexture* other) : AnimatedTexture(other->getTexture(), other->getDelay())
{
	const std::vector<SDL_Rect> lFrames = other->getFrames();
	std::vector<SDL_Rect>::const_iterator lFramesIt = lFrames.begin();

	while (lFramesIt != lFrames.end()) {
		this->addFrame((*lFramesIt).x, (*lFramesIt).y, (*lFramesIt).w, (*lFramesIt).h);
		lFramesIt++;
	}

}

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
		
			if (this->listener != nullptr) {
				this->listener->onAnimationEnded();
			}

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

void AnimatedTexture::setEventListener(AnimatedTextureEvent* eventlistener)
{
	this->listener = eventlistener;
}

std::vector<SDL_Rect> AnimatedTexture::getFrames()
{
	return this->frames;
}
