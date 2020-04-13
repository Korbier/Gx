#include "Bullet.h"

#include "game/bullet/BulletGenerator.h"

Bullet::Bullet(BulletDescriptor* descriptor, BulletGenerator* generator) : Sprite(descriptor->getFireTexture(), generator->getPosition(), { descriptor->getSize(),descriptor->getSize() })
{
	this->descriptor = descriptor;
	this->generator = generator;
	this->fireTexture = new AnimatedTexture(this->descriptor->getFireTexture());
	this->explosionTexture = new AnimatedTexture(this->descriptor->getExplosionTexture());
	this->explosionTexture->setEventListener(this);
	this->setVelocity({ (float) this->descriptor->getInitialVelocity().x,  (float) this->descriptor->getInitialVelocity().y });
	this->hitbox.setPosition({ 12, 12 });
	this->hitbox.setSize({ 8, 8 });
}

int Bullet::getState()
{
	return this->state;
}

void Bullet::setState(int state)
{
	this->state = state;

	if (this->state == 1) {
		this->getExplosionTexture()->play();
	}

}

AnimatedTexture* Bullet::getTexture()
{

	if (this->getState() == 1) {
		return this->getExplosionTexture();
	}

	return this->getFireTexture();

}

bool Bullet::isRenderable()
{
	return this->getState() == 0 || this->getState() == 1;
}

AnimatedTexture* Bullet::getFireTexture()
{
	return this->fireTexture;
}

AnimatedTexture* Bullet::getExplosionTexture()
{
	return this->explosionTexture;
}

void Bullet::onAnimationEnded()
{
	this->setState(2);
}
