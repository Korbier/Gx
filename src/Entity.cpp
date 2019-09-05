#include "Entity.h"

#include "AnimatedSprite.h"

Entity::Entity(AnimatedSprite* sprite, float x, float y)
{
	this->sprite = sprite;
	this->moveTo(x, y);
}

Entity::~Entity()
{
	delete this->sprite;
}

float Entity::getXVelocity()
{
	return this->xVelocity;
}

float Entity::getYVelocity()
{
	return this->yVelocity;
}

void Entity::setXVelocity(float xVelocity)
{
	this->xVelocity = xVelocity;
}

void Entity::setYVelocity(float yVelocity) {
	this->yVelocity = yVelocity;
}

float Entity::getX()
{
	return this->x;
}

float Entity::getY()
{
	return this->y;
}

void Entity::move(float x, float y)
{
	this->moveTo(this->x + x, this->y + y);
}

void Entity::moveTo(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Entity::getAngle()
{
	return this->angle;
}

void Entity::rotate(float angle)
{
	this->setAngle(this->angle + angle);
}

void Entity::setAngle(float angle)
{
	this->angle = angle;
}

AnimatedSprite* Entity::getSprite()
{
	return this->sprite;
}

