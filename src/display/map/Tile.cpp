#include "Tile.h"

Tile::Tile(Texture* tile, int angle, TileReference* reference)
{
	this->tile = tile;
	this->angle = angle;
	this->reference = reference;
}

Texture* Tile::getTile()
{
	return this->tile;
}

int Tile::getAngle()
{
	return this->angle;
}

TileReference* Tile::getReference()
{
	return this->reference;
}
