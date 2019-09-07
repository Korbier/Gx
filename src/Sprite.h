#pragma once

#include "SDL.h"

class Texture;
class AnimatedTexture;

class Sprite
{
public:
	
	Sprite(AnimatedTexture* Texture, float x, float y );
	~Sprite();

	float getXVelocity();
	float getYVelocity();
	void setXVelocity(float xVelocity);
	void setYVelocity(float yVelocity);

	float getX();
	float getY();
	void move(float x, float y);
	void moveTo(float x, float y);

	float getAngle();
	void rotate(float angle);
	void setAngle(float angle);

	AnimatedTexture* getTexture();
		
private:
	float x;
	float y;
	float xVelocity;
	float yVelocity;
	float angle;
	AnimatedTexture* Texture;
};

