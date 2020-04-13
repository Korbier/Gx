#include "Sprite.h"

Sprite::Sprite(AnimatedTexture* texture, SDL_FPoint position, SDL_Point size ) {
	this->texture = texture;
	this->setPosition( position );
	this->setVelocity({ 0, 0});
	this->size = { size.x, size.y };
	this->hitbox.setPosition({ 2, 2 });
	this->hitbox.setSize({ 28, 28 });
}

Sprite::~Sprite()
{
	delete this->texture;
}

SDL_FPoint Sprite::getVelocity()
{
	return this->velocity;
}

void Sprite::setVelocity(SDL_FPoint velocity)
{
	this->velocity = velocity;
}

SDL_FPoint Sprite::getPosition()
{
	return this->position;
}

void Sprite::move(SDL_FPoint position)
{
	SDL_FPoint current = this->getPosition();
	this->setPosition({ current.x + position.x, current.y + position.y });
}

SDL_Point Sprite::getSize()
{
	return this->size;
}

Hitbox Sprite::getHitbox()
{
	return this->hitbox;
}

SDL_FPoint Sprite::getHitboxCenter()
{
	float x1 = getPosition().x + getHitbox().getPosition().x;
	float x2 = getPosition().x + getHitbox().getPosition().x + getHitbox().getSize().x;
	float xCenter = (x1 + x2) / 2;

	float y1 = getPosition().y + getHitbox().getPosition().y;
	float y2 = getPosition().y + getHitbox().getPosition().y + getHitbox().getSize().y;
	float yCenter = (y1 + y2) / 2;

	return { xCenter, yCenter };
}

float Sprite::getHitboxRadius()
{
	return fminf( getHitbox().getSize().x / 2, getHitbox().getSize().y / 2 );
}

void Sprite::setPosition(SDL_FPoint position)
{
	this->position = position;
}

float Sprite::getAngle()
{
	return this->angle;
}

void Sprite::rotate(float angle)
{
	this->setAngle(this->angle + angle);
}

void Sprite::setAngle(float angle)
{
	this->angle = angle;
}

AnimatedTexture* Sprite::getTexture()
{
	return this->texture;
}

bool Sprite::isRenderable()
{
	return true;
}

