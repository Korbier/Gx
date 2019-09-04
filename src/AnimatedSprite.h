#pragma once

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(SDL_Texture* texture, int x, int y, Uint32 delay );
	void addFrame(int x, int y, int w, int h);
	
	void setDelay(Uint32 delay);
	Uint32 getDelay();

	void animate();
	void play();
	void pause();
private:
	Timer* timer = nullptr;
	size_t index = 0;
	Uint32 delay = 0;
	std::vector<SDL_Rect*> frames;
};

