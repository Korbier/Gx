#include "MapTileReference.h"

MapTileReference::MapTileReference(Tileset* tileset, int x, int y)
{
	this->tileset = tileset;
	this->autotile = false;
	this->merged = false;
	this->tileX = x;
	this->tileY = y;
}

MapTileReference::MapTileReference(Tileset* tileset, bool merged)
{
	this->tileset = tileset;
	this->autotile = true;
	this->merged = merged;
}

Tileset* MapTileReference::getTileset()
{
	return this->tileset;
}

int MapTileReference::getTileX()
{
	return this->tileX;
}

int MapTileReference::getTileY()
{
	return this->tileY;
}

bool MapTileReference::isAutoTile()
{
	return this->autotile;
}

bool MapTileReference::isMergedAutoTile()
{
	return this->merged;
}
