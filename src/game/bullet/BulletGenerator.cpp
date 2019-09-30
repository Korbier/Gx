#include "BulletGenerator.h"

BulletGenerator::BulletGenerator(BulletDescriptor* descriptor)
{
	this->descriptor = descriptor;
}

void BulletGenerator::fire()
{
	BOOST_LOG_TRIVIAL(info) << "Fire";
	if (this->canFire()) {
		
		BOOST_LOG_TRIVIAL(info) << "Effective fire";
		Bullet* b = nullptr;
		
		if (this->available.empty()) {
			b = new Bullet(this->descriptor, this);
		}
		else {
			b = this->available.back();
			this->available.pop_back();
		}

		this->fired.push_back(b);
		this->fireAvailable = false;
		this->currrentTime = 0;

		BOOST_LOG_TRIVIAL(info) << "Fired : " << this->fired.size();

	}
}

void BulletGenerator::release(Bullet* bullet)
{
	std::vector<Bullet*> v = this->fired;
	v.erase(std::remove(v.begin(), v.end(), bullet), v.end());
	this->available.push_back(bullet);
}

bool BulletGenerator::canFire() {
	return this->fireAvailable;
}

void BulletGenerator::update(Uint32 delta)
{
	this->currrentTime += delta;

	if (this->currrentTime > this->fireDelay) {
		this->currrentTime = 0;
		this->fireAvailable = true;
	}

	for (std::vector<Bullet*>::iterator it = this->fired.begin(); it != this->fired.end(); ++it) {
		Bullet* b = *it;
		b->move({ 
			this->descriptor->getInitialVelocity().x * (delta / 1000.f), 
			this->descriptor->getInitialVelocity().y * (delta / 1000.f),
		});
	}

}

void BulletGenerator::setPosition(SDL_FPoint position)
{
	this->position = position;
}

SDL_FPoint BulletGenerator::getPosition()
{
	return this->position;
}

void BulletGenerator::setDirection(float direction)
{
	this->direction = direction;
}

float BulletGenerator::getDirection()
{
	return this->direction;
}

void BulletGenerator::setFireDelay(int delay)
{
	this->fireDelay = fireDelay;
}

int BulletGenerator::getDelay()
{
	return this->fireDelay;
}

std::vector<Bullet*> BulletGenerator::getBulletsToRender()
{
	return this->fired;
}
