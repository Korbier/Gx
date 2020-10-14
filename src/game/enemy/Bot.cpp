#include "Bot.h"

Bot::Bot(Map* map, AnimatedTexture* texture, SDL_FPoint position, SDL_Point size):Sprite(texture, position, size)
{
	this->pathfinder = new Pathfinder(map);
	this->pathfinder->init();
}

void Bot::setTarget(Sprite* target)
{
	this->target = target;
}

void Bot::update(Uint32 delta)
{

	SDL_FPoint targetPoint = target->getHitboxCenter();

	this->pathfinder->reset();
	Node* node = this->pathfinder->find({ (int) getPosition().x / 32, (int)getPosition().y / 32 }, { (int)targetPoint.x / 32, (int)targetPoint.y / 32 });

	float xVal = 0;
	float yVal = 0;
		
	float xDistance = targetPoint.x - getHitboxCenter().x;
	float yDistance = targetPoint.y - getHitboxCenter().y;

	if (xDistance > 0) xVal = getVelocity().x * (delta / 1000.f);
	if (xDistance < 0) xVal = -1 * getVelocity().x * (delta / 1000.f);
	if (yDistance > 0) yVal = getVelocity().y * (delta / 1000.f);
	if (yDistance < 0) yVal = -1 * getVelocity().y * (delta / 1000.f);

	float rAngle = atanf(yDistance / xDistance);
	setAngle(rAngle / M_PI * 180.0 + 90);

	float xCorrectedVal = this->map->checKCollisionX(this, xVal);
	float yCorrectedVal = this->map->checKCollisionY(this, yVal);
		
	if (xCorrectedVal != 0) {
		move({ xCorrectedVal, 0 });
	}

	if (yCorrectedVal != 0) {
		move({ 0, yCorrectedVal });
	}

	getTexture()->animate();
	

}
