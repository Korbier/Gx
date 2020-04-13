#include "BulletGenerator.h"

BulletGenerator::BulletGenerator(BulletDescriptor* descriptor)
{
	this->descriptor = descriptor;
}

void BulletGenerator::fire( float direction )
{
	if (this->canFire()) {
		
		Bullet* b = nullptr;
		
		if (this->available.empty()) {
			b = new Bullet(this->descriptor, this);
		}
		else {
			b = this->available.back();
			this->available.pop_back();
		}

		b->setPosition(this->getPosition());
		b->setAngle(direction);

		this->fired.push_back(b);
		this->fireAvailable = false;
		this->currrentTime = 0;

		SDL_FPoint mvt = radMvtToCoord(b->getAngle(), 15);
		b->move(mvt);

	}
}

bool BulletGenerator::canFire() {
	return this->fireAvailable;
}

void BulletGenerator::update( Map * map, Uint32 delta)
{

	this->clearUnactiveBullets();

	this->currrentTime += delta;

	if (this->currrentTime > this->fireDelay) {
		this->currrentTime = 0;
		this->fireAvailable = true;
	}

	for (std::vector<Bullet*>::iterator it = this->fired.begin(); it != this->fired.end(); ++it) {
		
		if ((*it)->isRenderable()) {
			(*it)->getTexture()->animate();
		}

		if ( (*it)->getState() == 0) {

			SDL_Point cell = map->getCellForRadialCollision(*it);

			if (map->checkBallCollision(cell)) {
				
				BOOST_LOG_TRIVIAL(error) << "Collision !\n";
			
				if ((*it)->getRemainingBounces() > 0) {
					
					SDL_FPoint sCenter = (*it)->getHitboxCenter();
					SDL_Point target = { sCenter.x / 32, sCenter.y / 32 };

					if (cell.x != target.x) {
						(*it)->bounceVertical();
					}
					else {
						(*it)->bounceHorizontal();
					}

					
				}
				else {
					(*it)->setState(1);
				}

			}
			else {
				float distance = (*it)->getVelocity().x * (delta / 1000.f);
				SDL_FPoint mvt = radMvtToCoord((*it)->getAngle(), distance);
				(*it)->move(mvt);
			}

		}
	}

}

void BulletGenerator::clearUnactiveBullets()
{

	auto end = std::remove_if(this->fired.begin(), this->fired.end(), []( Bullet * bullet) {
		return bullet->getState() > 1;
	});

	this->fired.erase(end, this->fired.end());

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
