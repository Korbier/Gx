#include "Tileset.h"

#include "texture/Texture.h"

void Tileset::loadTileset(SDL_Texture* sdlTexture, int tileSize )
{
	this->texture = sdlTexture;
	SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

	this->width  = this->width / tileSize;
	this->height = this->height / tileSize;

	this->tiles = new Texture ** [this->width];

	for (int i = 0; i < this->width; i++) {

		this->tiles[i] = new Texture* [this->height];

		for (int j = 0; j < this->height; j++) {
			SDL_Rect rect;
			rect.x = i * tileSize;
			rect.y = j * tileSize;
			rect.w = rect.h = tileSize;
			this->tiles[i][j] = new Texture(this->texture, rect);
		}
	}

}

Texture* Tileset::getTile(int xIndex, int yIndex)
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
