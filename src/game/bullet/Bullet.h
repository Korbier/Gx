#pragma once

#include "display/Sprite.h"
#include "game/bullet/BulletDescriptor.h"

class BulletGenerator;

class Bullet: public Sprite
{
public:
	Bullet(BulletDescriptor* descriptor, BulletGenerator* generator);
private:
	BulletDescriptor* descriptor;
	BulletGenerator* generator;
};

