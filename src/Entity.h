#pragma once

#include "SDL.h"

class Sprite;
class AnimatedSprite;

class Entity
{
public:
	
	Entity(AnimatedSprite* sprite, float x, float y );
	~Entity();

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

	AnimatedSprite* getSprite();
		
private:
	float x;
	float y;
	float xVelocity;
	float yVelocity;
	float angle;
	AnimatedSprite* sprite;
};

