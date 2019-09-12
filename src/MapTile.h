#pragma once

class Tile;

class MapTile
{
public:
	MapTile(Tile* tile, int angle, bool solid);
	Tile* getTile();
	int getAngle();
	bool isSolid();
private:
	Tile* tile = nullptr;
	int angle = 0;
	bool solid = false;
};

