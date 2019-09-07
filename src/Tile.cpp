#include "Tile.h"

#include "AnimatedTexture.h"

Tile::Tile(Texture* texture)
{
	this->texture = texture;
}

Tile::Tile():Tile(nullptr)
{
}

Tile::~Tile()
{
	delete this->texture;
}

void Tile::setTexture(Texture* texture)
{
	this->texture = texture;
}

Texture* Tile::getTexture()
{
	return this->texture;
}
