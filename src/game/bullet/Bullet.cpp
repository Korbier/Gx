#include "Bullet.h"

#include "game/bullet/BulletGenerator.h"

Bullet::Bullet(BulletDescriptor* descriptor, BulletGenerator* generator) : Sprite(descriptor->getFireTexture(), generator->getPosition(), { descriptor->getSize(),descriptor->getSize() })
{
	this->descriptor = descriptor;
	this->generator = generator;
}
