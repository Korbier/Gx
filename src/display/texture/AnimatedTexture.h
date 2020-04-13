#pragma once

#include <vector>

#include <SDL.h>

#include "boost/log/trivial.hpp"

#include "display/texture/Texture.h"
#include "display/texture/AnimatedTextureEvent.h"
#include "utils/Timer.h"

class AnimatedTexture : public Texture
{
public:
	AnimatedTexture(AnimatedTexture* other);
	AnimatedTexture(SDL_Texture* texture, float delay);
	AnimatedTexture(SDL_Texture* texture);
	~AnimatedTexture();

	void addFrame(int x, int y, int w, int h);
	
	void setDelay(float delay);
	float getDelay();

	void animate();
	void play();
	void pause();

	void setEventListener(AnimatedTextureEvent* eventlistener);

	std::vector<SDL_Rect> getFrames();

private:
	Timer timer;
	size_t index = 0;
	float delay = 0;
	std::vector<SDL_Rect> frames;
	AnimatedTextureEvent * listener = nullptr;

};

