#pragma once

#include <string>
#include "SDL.h"

class Tile;

class Tileset
{
public:
	void loadTileset(SDL_Texture* texture, int tileSize);
	Tile* getTile(int xIndex, int yIndex);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture = nullptr;
	Tile*** tiles = {};
	int width;
	int height;
	
};

