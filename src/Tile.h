#pragma once

#include "SDL.h"

class Texture;

class Tile
{
public:

	Tile(Texture* texture);
	Tile();

	~Tile();

	void setTexture(Texture* texture);
	Texture* getTexture();

private:
	Texture* texture;
};

