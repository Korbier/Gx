#include "MapTile.h"

MapTile::MapTile(Texture* tile, int angle, bool solid)
{
	this->tile = tile;
	this->angle = angle;
	this->solid = solid;
}

Texture* MapTile::getTile()
{
	return this->tile;
}

int MapTile::getAngle()
{
	return this->angle;
}

bool MapTile::isSolid()
{
	return this->solid;
}
