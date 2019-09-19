#pragma once

#include <map>
#include "Sprite.h"

class AnimatedTexture;
class Sprite;

class Bullet: public Sprite
{
public:
	Bullet(AnimatedTexture* texture, SDL_FPoint position, SDL_Point size);
	void setTexture(int state, AnimatedTexture* texture);
	AnimatedTexture* getTexture();
	void setState(int state);

private:
	std::map<int, AnimatedTexture*> textures;
	int state = 0;
};

