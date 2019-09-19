#pragma once

#include <string>
#include "SDL.h"

class Texture;

class Tileset
{
public:
	void loadTileset(SDL_Texture* texture, int tileSize);
	Texture* getTile(int xIndex, int yIndex);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture = nullptr;
	Texture*** tiles = {};
	int width;
	int height;
	
};

