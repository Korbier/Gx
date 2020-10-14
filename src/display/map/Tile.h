#pragma once

#include "display/texture/Texture.h"
#include "display/map/TileReference.h"

class Tile
{
public:
	Tile(Texture* tile, int angle, TileReference* reference);
	Texture* getTile();
	int getAngle();
	TileReference* getReference();
private:
	Texture* tile = nullptr;
	int angle = 0;
	TileReference* reference;
};

