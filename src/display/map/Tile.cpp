#include "Tile.h"

Tile::Tile(Texture* tile, int angle, bool solid)
{
	this->tile = tile;
	this->angle = angle;
	this->solid = solid;
}

Texture* Tile::getTile()
{
	return this->tile;
}

int Tile::getAngle()
{
	return this->angle;
}

bool Tile::isSolid()
{
	return this->solid;
}
