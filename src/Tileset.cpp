#include "Tileset.h"

#include "Tile.h"
#include "Texture.h"

void Tileset::loadTileset(SDL_Texture* sdlTexture, int tileSize )
{
	this->texture = sdlTexture;
	SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

	this->width  = this->width / tileSize;
	this->height = this->height / tileSize;

	this->tiles = new Tile** [this->width];

	for (int i = 0; i < this->width; i++) {

		this->tiles[i] = new Tile* [this->height];

		for (int j = 0; j < this->height; j++) {
			SDL_Rect* rect = new SDL_Rect();
			rect->x = i * tileSize;
			rect->y = j * tileSize;
			rect->w = rect->h = tileSize;
			Texture* texture = new Texture(this->texture, rect);
			this->tiles[i][j] = new Tile(texture);

		}
	}
}

Tile* Tileset::getTile(int xIndex, int yIndex)
{
	return this->tiles[xIndex][yIndex];
}

int Tileset::getWidth()
{
	return this->width;
}

int Tileset::getHeight()
{
	return this->height;
}
