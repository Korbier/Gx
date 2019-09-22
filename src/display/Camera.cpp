#include "Camera.h"

void Camera::setPosition(SDL_FPoint position)
{
	this->position = position;
}

void Camera::setSize(int width, int height)
{
	this->size.x = width;
	this->size.y = height;
}

void Camera::move(float x, float y)
{
	this->position.x = this->position.x + x;
	this->position.y = this->position.y + y;
}

SDL_FPoint Camera::getPosition()
{
	return this->position;
}

SDL_Point Camera::getSize()
{
	return this->size;
}

void Camera::toCameraView(SDL_Point* point)
{
	point->x = point->x - (int) this->getPosition().x;
	point->y = point->y - (int) this->getPosition().y;
}

void Camera::toCameraView(SDL_Rect* rect)
{
	rect->x = rect->x - (int) this->getPosition().x;
	rect->y = rect->y - (int) this->getPosition().y;
}

void Camera::toWorldView(SDL_Point* point)
{
	point->x = point->x + (int) this->getPosition().x;
	point->y = point->y + (int) this->getPosition().y;
}
