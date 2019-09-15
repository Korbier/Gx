#include "Map.h"

#include <vector>
#include <sstream>
#include <string>

#include "boost/log/trivial.hpp"
#include "MapTileReference.h"
#include "Tileset.h"
#include "MapTile.h"
#include "Sprite.h"

Map::Map() {
}

void Map::addReference(int index, Tileset* tileset, bool solid, int tileX, int tileY)
{
	BOOST_LOG_TRIVIAL(info) << "Tileset : " << tileset;

	MapTileReference* reference = new MapTileReference(tileset, solid, tileX, tileY);
	this->references.insert(std::pair<int, MapTileReference*>(index, reference));
}

void Map::addReference(int index, Tileset* tileset, bool solid, bool merged)
{
	MapTileReference* reference = new MapTileReference(tileset, solid, merged);
	this->references.insert(std::pair<int, MapTileReference*>(index, reference));
}

void Map::setData(std::vector<std::vector<int>> data, int width, int height)
{

	this->data = data;
	this->width = width;
	this->height = height;

	this->loadIndexes();
	this->loadRotations();
	this->loadCache();

}

void Map::debug() {

	std::stringstream messageMap;
	std::stringstream message;

	for (int j = 0; j < this->height; j++) {
		for (int i = 0; i < this->width; i++) {

			int cell = this->data[i][j];
			int value = cell == 1 ? this->toAutoTileIndex(cell, this->references[cell], i, j) : 0;

			message << " {" << std::to_string(value) << "}";
			messageMap << "[" << std::to_string(cell) << "]";

		}

		message << "\n";
		messageMap << "\n";

	}

	BOOST_LOG_TRIVIAL(info) << "\n" << messageMap.str();
	BOOST_LOG_TRIVIAL(info) << "\n" << message.str();

}
MapTile* Map::getTileAt(int x, int y)
{
	return this->cache[x][y];
}

void Map::boundToMap(Sprite* sprite)
{

	SDL_FPoint sPosition = sprite->getPosition();
	SDL_Point  sSize = sprite->getSize();

	SDL_FPoint newPosition = { sPosition.x, sPosition.y };

	if (sPosition.x < 0.f) newPosition.x = 0.f;
	if (sPosition.y < 0.f) newPosition.y = 0.f;
	if (sPosition.x + sSize.x > this->getWidth() * 32)  newPosition.x = (float) this->getWidth() * 32 - sSize.x;
	if (sPosition.y + sSize.y > this->getHeight() * 32) newPosition.y = (float) this->getHeight() * 32 - sSize.y;

	sprite->setPosition(newPosition);

}

SDL_FPoint Map::checkCollision(Sprite* sprite, SDL_FPoint decal)
{

	SDL_FPoint newDecal = { decal.x, decal.y };
	SDL_FPoint newPosition = { sprite->getPosition().x, sprite->getPosition().y };

	if (decal.x > 0) {
		
		float xCoord  = sprite->getPosition().x + sprite->getSize().x + decal.x;
		float yCoord  = sprite->getPosition().y;
		float yCoord2 = sprite->getPosition().y + sprite->getSize().y - 1;

		int cellXCoord  = (int) xCoord  / 32;
		int cellYCoord  = (int) yCoord  / 32;
		int cellY2Coord = (int) yCoord2 / 32;
		
		float pixelCellXCoord = cellXCoord * 32;

		int cell = this->getData(cellXCoord, cellYCoord);
		int cell2 = this->getData(cellXCoord, cellY2Coord);
		if (this->references[cell]->isSolid() || this->references[cell2]->isSolid()) {
			newPosition.x = pixelCellXCoord - sprite->getSize().x;
		}

	} 
	
	if (decal.x < 0) {

		float xCoord = sprite->getPosition().x + decal.x;
		float yCoord = sprite->getPosition().y;
		float yCoord2 = sprite->getPosition().y + sprite->getSize().y - 1;

		int cellXCoord  = (int) xCoord / 32;
		int cellYCoord  = (int) yCoord / 32;
		int cellY2Coord = (int) yCoord2 / 32;

		float pixelCellXCoord = cellXCoord * 32;

		int cell = this->getData(cellXCoord, cellYCoord);
		int cell2 = this->getData(cellXCoord, cellY2Coord);
		if (this->references[cell]->isSolid() || this->references[cell2]->isSolid()) {
			newPosition.x = pixelCellXCoord + 32;
		}

	}

	if (decal.y > 0) {

		float yCoord = sprite->getPosition().y + sprite->getSize().y + decal.y;
		float xCoord = sprite->getPosition().x;
		float xCoord2 = sprite->getPosition().x + sprite->getSize().x - 1;

		int cellXCoord  = (int)xCoord / 32;
		int cellX2Coord = (int)xCoord2 / 32;
		int cellYCoord  = (int)yCoord / 32;
		
		float pixelCellYCoord = cellYCoord * 32;

		int cell = this->getData(cellXCoord, cellYCoord);
		int cell2 = this->getData(cellX2Coord, cellYCoord);
		if (this->references[cell]->isSolid() || this->references[cell2]->isSolid()) {
			newPosition.y = pixelCellYCoord - sprite->getSize().y;
		}

	}
	
	if (decal.y < 0) {

		float yCoord = sprite->getPosition().y + decal.y;
		float xCoord = sprite->getPosition().x;
		float xCoord2 = sprite->getPosition().x + sprite->getSize().x - 1;

		int cellXCoord = (int)xCoord / 32;
		int cellX2Coord = (int)xCoord2 / 32;
		int cellYCoord = (int)yCoord / 32;

		float pixelCellYCoord = cellYCoord * 32;

		int cell = this->getData(cellXCoord, cellYCoord);
		int cell2 = this->getData(cellX2Coord, cellYCoord);
		if (this->references[cell]->isSolid() || this->references[cell2]->isSolid()) {
			newPosition.y = pixelCellYCoord + 32;
		}

	}

	sprite->setPosition(newPosition);
	return newDecal;
}

int Map::getWidth()
{
	return this->width;
}

int Map::getHeight()
{
	return this->height;
}

void Map::loadRotations()
{
	for (int i = 0; i < 255; i++) {
		this->rotations.insert({ i,0 });
	}

	this->rotations[0]=0;
	this->rotations[1]=0;
	this->rotations[4]=90;
	this->rotations[16]=180;
	this->rotations[64]=270;
	this->rotations[5]=0;
	this->rotations[20]=90;
	this->rotations[80]=180;
	this->rotations[65]=270;
	this->rotations[7]=0;
	this->rotations[28]=90;
	this->rotations[112]=180;
	this->rotations[193]=270;
	this->rotations[17]=0;
	this->rotations[68]=90;
	this->rotations[21]=0;
	this->rotations[84]=90;
	this->rotations[81]=180;
	this->rotations[69]=270;
	this->rotations[23]=0;
	this->rotations[92]=90;
	this->rotations[113]=180;
	this->rotations[197]=270;
	this->rotations[29]=0;
	this->rotations[116]=90;
	this->rotations[209]=180;
	this->rotations[71]=270;
	this->rotations[31]=0;
	this->rotations[124]=90;
	this->rotations[241]=180;
	this->rotations[199]=270;
	this->rotations[85]=0;
	this->rotations[87]=0;
	this->rotations[93]=90;
	this->rotations[117]=180;
	this->rotations[213]=270;
	this->rotations[95]=0;
	this->rotations[125]=90;
	this->rotations[245]=180;
	this->rotations[215]=270;
	this->rotations[119]=0;
	this->rotations[221]=90;
	this->rotations[127]=0;
	this->rotations[253]=90;
	this->rotations[247]=180;
	this->rotations[223]=270;
	this->rotations[255]=0;

}

void Map::loadIndexes()
{
	for (int i = 0; i <= 255; i++) {
		this->indexes.insert({ i,  {0,0} });
	}

	this->indexes[0] = {0, 0};
	this->indexes[1] = {1, 0};
	this->indexes[4] = {1, 0};
	this->indexes[16] = {1, 0};
	this->indexes[64] = {1, 0};
	this->indexes[5] = {2, 0};
	this->indexes[20] = {2, 0};
	this->indexes[80] = {2, 0};
	this->indexes[65] = {2, 0};
	this->indexes[7] = {3, 0};
	this->indexes[28] = {3, 0};
	this->indexes[112] = {3, 0};
	this->indexes[193] = {3, 0};
	this->indexes[17] = {4, 0};
	this->indexes[68] = {4, 0};
	this->indexes[21] = {5, 0};
	this->indexes[84] = {5, 0};
	this->indexes[81] = {5, 0};
	this->indexes[69] = {5, 0};
	this->indexes[23] = {6, 0};
	this->indexes[92] = {6, 0};
	this->indexes[113] = {6, 0};
	this->indexes[197] = {6, 0};
	this->indexes[29] = {7, 0};
	this->indexes[116] = {7, 0};
	this->indexes[209] = {7, 0};
	this->indexes[71] = {7, 0};
	this->indexes[31] = {8, 0};
	this->indexes[124] = {8, 0};
	this->indexes[241] = {8, 0};
	this->indexes[199] = {8, 0};
	this->indexes[85] = {9, 0};
	this->indexes[87] = {10, 0};
	this->indexes[93] = {10, 0};
	this->indexes[117] = {10, 0};
	this->indexes[213] = {10, 0};
	this->indexes[95] = {11, 0};
	this->indexes[125] = {11, 0};
	this->indexes[245] = {11, 0};
	this->indexes[215] = {11, 0};
	this->indexes[119] = {12, 0};
	this->indexes[221] = {12, 0};
	this->indexes[127] = {13, 0};
	this->indexes[253] = {13, 0};
	this->indexes[247] = {13, 0};
	this->indexes[223] = {13, 0};
	this->indexes[255] = {14, 0};

}

void Map::loadCache()
{

	for (int i = 0; i < this->getWidth(); i++) {
		std::vector<MapTile*> row;
		for (int j = 0; j < this->getHeight(); j++) {
	
			int data = this->getData(i, j);
			MapTileReference* reference = this->references[data];
			Tile* tile = nullptr;
			int angle = 0;

			//BOOST_LOG_TRIVIAL(info) << "Data : " << data;

			if (reference->isAutoTile()) {
				
				int autoIndex = this->toAutoTileIndex(data, reference, i, j);
				
				//Recuperation du tile
				std::pair<int, int> tileIndex = this->indexes[autoIndex];
				tile = reference->getTileset()->getTile(tileIndex.first, tileIndex.second);

				//Recuperation de la rotation
				angle = this->rotations[autoIndex];

			}
			else {
				tile = reference->getTileset()->getTile(
					reference->getTileX(),
					reference->getTileY()
				);
			}

			row.push_back( new MapTile(tile, angle, reference) );

		}
		this->cache.push_back(row);
	}
}

bool Map::isNeighbour(int data, MapTileReference* reference, int x, int y) {

	if (x < 0) return true;
	if (y < 0) return true;
	if (x >= this->getWidth()) return true;
	if (y >= this->getHeight()) return true;

	bool value = this->getData(x, y) == data;

	if (reference->isMergedAutoTile()) {
		return value |= this->getData(x, y) != 0;
		// MapTileReference* otherRef = this->references[this->getData(x, y)];
		// value |= otherRef->isMergedAutoTile();
	}

	return value;

}

int Map::toAutoTileIndex(int data, MapTileReference* reference, int x, int y) {

	int value = 0;
	
	bool n = this->isNeighbour(data, reference, x, y - 1);
	bool ne = this->isNeighbour(data, reference, x + 1, y - 1);
	bool e = this->isNeighbour(data, reference, x + 1, y);
	bool se = this->isNeighbour(data, reference, x + 1, y + 1);
	bool s = this->isNeighbour(data, reference, x, y + 1);
	bool sw = this->isNeighbour(data, reference, x - 1, y + 1);
	bool w = this->isNeighbour(data, reference, x - 1, y);
	bool nw = this->isNeighbour(data, reference, x - 1, y - 1);

	value += n ? 1 : 0;
	value += (n && ne & e) ? 2 : 0;
	value += e ? 4 : 0;
	value += (e && se && s) ? 8 : 0;
	value += s ? 16 : 0;
	value += (s && sw && w) ? 32 : 0;
	value += w ? 64 : 0;
	value += (w && nw && n) ? 128 : 0;

	return value;

}
int Map::getData(int x, int y) {
	return this->data[x][y];
}



