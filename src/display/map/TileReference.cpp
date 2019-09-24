#include "TileReference.h"

TileReference::TileReference(Tileset* tileset, bool solid, int x, int y)
{
	this->tileset = tileset;
	this->solid = solid;
	this->autotile = false;
	this->merged = false;
	this->tileX = x;
	this->tileY = y;
}

TileReference::TileReference(Tileset* tileset, bool solid, bool merged)
{
	this->tileset = tileset;
	this->solid = solid;
	this->autotile = true;
	this->merged = merged;
}

Tileset* TileReference::getTileset()
{
	return this->tileset;
}

int TileReference::getTileX()
{
	return this->tileX;
}

int TileReference::getTileY()
{
	return this->tileY;
}

bool TileReference::isAutoTile()
{
	return this->autotile;
}

bool TileReference::isMergedAutoTile()
{
	return this->merged;
}

bool TileReference::isSolid() {
	return this->solid;
}