#pragma once

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(SDL_Texture* texture, float delay);
	void addFrame(int x, int y, int w, int h);
	
	void setDelay(float delay);
	float getDelay();

	void animate();
	void play();
	void pause();
private:
	Timer* timer = nullptr;
	size_t index = 0;
	float delay = 0;
	std::vector<SDL_Rect*> frames;
};

