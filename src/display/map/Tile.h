#pragma once

#include "display/texture/Texture.h"

class Tile
{
public:
	Tile(Texture* tile, int angle, bool solid);
	Texture* getTile();
	int getAngle();
	bool isSolid();
private:
	Texture* tile = nullptr;
	int angle = 0;
	bool solid = false;
};

