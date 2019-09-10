#pragma once

class Tileset;

class MapTileReference
{
public:
	MapTileReference(Tileset* tilset, int x, int y);
	MapTileReference(Tileset* tilset, bool merged);

	Tileset* getTileset();
	int getTileX();
	int getTileY();
	bool isAutoTile();
	bool isMergedAutoTile();
private:
	Tileset* tileset = nullptr;
	int tileX = 0;
	int tileY = 0;
	bool autotile = false;
	bool merged = false;
};
