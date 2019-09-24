#pragma once

#include "display/Tileset.h"

class TileReference
{
public:
	TileReference(Tileset* tilset, bool solid, int x, int y);
	TileReference(Tileset* tilset, bool solid, bool merged);

	Tileset* getTileset();
	
	bool isSolid();

	int getTileX();
	int getTileY();
	
	bool isAutoTile();
	bool isMergedAutoTile();


private:
	
	Tileset* tileset = nullptr;
	
	bool solid = false;

	/*Manuel tiling*/
	int tileX = 0;
	int tileY = 0;

	/*Autotiling*/
	bool autotile = false;
	bool merged = false;

};
