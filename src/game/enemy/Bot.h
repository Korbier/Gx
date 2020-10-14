#pragma once

#include "display/Sprite.h"
#include "game/pathfinding/Pathfinder.h"

class Bot : public Sprite {
public:
	Bot(Map * map, AnimatedTexture* texture, SDL_FPoint position, SDL_Point size);
	void setTarget(Sprite* target);
	void update(Uint32 delta);
private:
	Map* map;
	Sprite* target;
	Pathfinder* pathfinder;

};