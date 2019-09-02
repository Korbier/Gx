#pragma once

#include <SDL.h>
#include "Sprite.h"
#include "Timer.h"
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(SDL_Texture* texture, SDL_Rect* crop, int x, int y, int size);
	void update();
	void play();
	void pause();
private:
	Timer* timer = nullptr;
};

