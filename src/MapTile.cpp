#include "MapTile.h"

MapTile::MapTile(Tile* tile, int angle, bool solid)
{
	this->tile = tile;
	this->angle = angle;
	this->solid = solid;
}

Tile* MapTile::getTile()
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
