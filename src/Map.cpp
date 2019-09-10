#include "Map.h"

#include <vector>
#include "MapTileReference.h"
#include "Tileset.h"

Map::Map() {
	this->loadIndexes();
	this->loadRotations();
}

void Map::addReference(int index, Tileset* tileset, int tileX, int tileY)
{
	MapTileReference* reference = new MapTileReference(tileset, tileX, tileY);
	this->references.insert(std::pair<int, MapTileReference*>(index, reference));
}

void Map::addReference(int index, Tileset* tileset, bool merged)
{
	MapTileReference* reference = new MapTileReference(tileset, merged);
	this->references.insert(std::pair<int, MapTileReference*>(index, reference));
}

void Map::setData(std::vector<std::vector<int>> data)
{
	this->data = data;
}

Tile* Map::getTileAt(int x, int y)
{
	int data = this->data[x][y];
	MapTileReference* reference = this->references[data];

	if (reference->isAutoTile()) {
		return this->getAutoTile(reference);
	}
	else {
		return reference->getTileset()->getTile(
			reference->getTileX(),
			reference->getTileY()
		);
	}
	return nullptr;
}

void Map::loadRotations()
{
	for (int i = 0; i < 255; i++) {
		this->rotations.insert(std::pair<int, int>(i, 0));
	}

	this->rotations.insert(std::pair<int,int>(0,0));
	this->rotations.insert(std::pair<int,int>(1,0));
	this->rotations.insert(std::pair<int,int>(4,90));
	this->rotations.insert(std::pair<int,int>(16,180));
	this->rotations.insert(std::pair<int,int>(64,270));
	this->rotations.insert(std::pair<int,int>(5,0));
	this->rotations.insert(std::pair<int,int>(20,90));
	this->rotations.insert(std::pair<int,int>(80,180));
	this->rotations.insert(std::pair<int,int>(65,270));
	this->rotations.insert(std::pair<int,int>(7,0));
	this->rotations.insert(std::pair<int,int>(28,90));
	this->rotations.insert(std::pair<int,int>(112,180));
	this->rotations.insert(std::pair<int,int>(193,270));
	this->rotations.insert(std::pair<int,int>(17,0));
	this->rotations.insert(std::pair<int,int>(68,90));
	this->rotations.insert(std::pair<int,int>(21,0));
	this->rotations.insert(std::pair<int,int>(84,90));
	this->rotations.insert(std::pair<int,int>(81,180));
	this->rotations.insert(std::pair<int,int>(69,270));
	this->rotations.insert(std::pair<int,int>(23,0));
	this->rotations.insert(std::pair<int,int>(92,90));
	this->rotations.insert(std::pair<int,int>(113,180));
	this->rotations.insert(std::pair<int,int>(197,270));
	this->rotations.insert(std::pair<int,int>(29,0));
	this->rotations.insert(std::pair<int,int>(116,90));
	this->rotations.insert(std::pair<int,int>(209,180));
	this->rotations.insert(std::pair<int,int>(71,270));
	this->rotations.insert(std::pair<int,int>(31,0));
	this->rotations.insert(std::pair<int,int>(124,90));
	this->rotations.insert(std::pair<int,int>(241,180));
	this->rotations.insert(std::pair<int,int>(199,270));
	this->rotations.insert(std::pair<int,int>(85,0));
	this->rotations.insert(std::pair<int,int>(87,0));
	this->rotations.insert(std::pair<int,int>(93,90));
	this->rotations.insert(std::pair<int,int>(117,180));
	this->rotations.insert(std::pair<int,int>(213,270));
	this->rotations.insert(std::pair<int,int>(95,0));
	this->rotations.insert(std::pair<int,int>(125,90));
	this->rotations.insert(std::pair<int,int>(245,180));
	this->rotations.insert(std::pair<int,int>(215,270));
	this->rotations.insert(std::pair<int,int>(119,0));
	this->rotations.insert(std::pair<int,int>(221,90));
	this->rotations.insert(std::pair<int,int>(127,0));
	this->rotations.insert(std::pair<int,int>(253,90));
	this->rotations.insert(std::pair<int,int>(247,180));
	this->rotations.insert(std::pair<int,int>(223,270));
	this->rotations.insert(std::pair<int,int>(255,0));

}

void Map::loadIndexes()
{
	for (int i = 0; i < 255; i++) {
		this->indexes.insert(std::pair<int, std::pair<int,int>>(i, std::pair<int,int>(0,0)));
	}

	this->indexes.insert(std::pair<int, std::pair<int,int>>(0,  std::pair<int,int>(0, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(1, std::pair<int, int>(1, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(4, std::pair<int, int>(1, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(16, std::pair<int, int>(1, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(64, std::pair<int, int>(1, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(5, std::pair<int, int>(2, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(20, std::pair<int, int>(2, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(80, std::pair<int, int>(2, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(65, std::pair<int, int>(2, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(7, std::pair<int, int>(3, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(28, std::pair<int, int>(3, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(112, std::pair<int, int>(3, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(193, std::pair<int, int>(3, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(17, std::pair<int, int>(4, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(68, std::pair<int, int>(4, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(21, std::pair<int, int>(5, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(84, std::pair<int, int>(5, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(81, std::pair<int, int>(5, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(69, std::pair<int, int>(5, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(23, std::pair<int, int>(6, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(92, std::pair<int, int>(6, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(113, std::pair<int, int>(6, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(197, std::pair<int, int>(6, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(29, std::pair<int, int>(7, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(116, std::pair<int, int>(7, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(209, std::pair<int, int>(7, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(71, std::pair<int, int>(7, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(31, std::pair<int, int>(8, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(124, std::pair<int, int>(8, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(241, std::pair<int, int>(8, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(199, std::pair<int, int>(8, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(85, std::pair<int, int>(9, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(87, std::pair<int, int>(10, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(93, std::pair<int, int>(10, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(117, std::pair<int, int>(10, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(213, std::pair<int, int>(10, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(95, std::pair<int, int>(11, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(125, std::pair<int, int>(11, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(245, std::pair<int, int>(11, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(215, std::pair<int, int>(11, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(119, std::pair<int, int>(12, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(221, std::pair<int, int>(12, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(127, std::pair<int, int>(13, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(253, std::pair<int, int>(13, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(247, std::pair<int, int>(13, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(223, std::pair<int, int>(13, 0)));
	this->indexes.insert(std::pair<int, std::pair<int, int>>(255, std::pair<int, int>(14,0)));

}

Tile* Map::getAutoTile(MapTileReference* reference)
{
	return nullptr; //cf TileMap.getvalue()
}



