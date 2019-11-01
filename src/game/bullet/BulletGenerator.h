#pragma once

#include <vector>
#include <algorithm>

#include <SDL.h>

#include "boost/log/trivial.hpp"

#include "game/bullet/Bullet.h"
#include "game/bullet/BulletDescriptor.h"

class BulletGenerator
{
public:
	
	BulletGenerator(BulletDescriptor* descriptor);
	
	void fire(float direction);
	void release(Bullet* bullet);
	bool canFire();

	void update(Uint32 delay);

	void setPosition(SDL_FPoint position);
	SDL_FPoint getPosition();

	void setDirection(float direction);
	float getDirection();

	void setFireDelay(int delay);
	int getDelay();

	std::vector<Bullet*> getBulletsToRender();

private:
	
	BulletDescriptor* descriptor = nullptr;

	SDL_FPoint position = {};	
	float direction = 0.f;

	int fireDelay = 60;
	int currrentTime = 0;
	bool fireAvailable = true;

	std::vector<Bullet*> fired = {};
	std::vector<Bullet*> available = {};


};

