#pragma once

#include "display/Sprite.h"
#include "game/bullet/BulletDescriptor.h"
#include "display/texture/AnimatedTextureEvent.h"

class BulletGenerator;

class Bullet: public Sprite, AnimatedTextureEvent
{
public:
	Bullet(BulletDescriptor* descriptor, BulletGenerator* generator);
	int getState();
	void setState(int state);

	AnimatedTexture* getTexture();
	bool isRenderable();
	
	int getRemainingBounces();
	void bounceHorizontal();
	void bounceVertical();

	AnimatedTexture* getFireTexture();
	AnimatedTexture* getExplosionTexture();

	void onAnimationEnded();

private:
	BulletDescriptor* descriptor;
	BulletGenerator* generator;
	int state = 0;
	int bounces = 20;
	AnimatedTexture* fireTexture;
	AnimatedTexture* explosionTexture;

};

