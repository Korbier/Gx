#pragma once

#include "SDL.h"

class Sprite;

class BulletManager
{
public:
	void fire();
	void update(Uint32 delta);
};

