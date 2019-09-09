#include "TileMap.h"

#include "boost/log/trivial.hpp"
#include <sstream>
#include <string>

#include "Tileset.h"
#include "Tile.h"
#include "Texture.h"

TileMap::TileMap(std::vector<std::vector<int>> map, int width, int height)
{

	this->map = map;
	this->width  = width;
	this->height = height;
	
}

void TileMap::load(Tileset* tilset)
{

	for (int i = 0; i < 255; i++) {
		this->setMapping(i, tilset->getTile(0, 0), 0);
	}

	this->setMapping(0, tilset->getTile(0, 0), 0);

	this->setMapping(1, tilset->getTile(1, 0),  0);
	this->setMapping(4, tilset->getTile(1, 0),  90);
	this->setMapping(16, tilset->getTile(1, 0), 180);
	this->setMapping(64, tilset->getTile(1, 0), 270);

	this->setMapping(5,  tilset->getTile(2, 0), 0);
	this->setMapping(20, tilset->getTile(2, 0), 90);
	this->setMapping(80, tilset->getTile(2, 0), 180);
	this->setMapping(65, tilset->getTile(2, 0), 270);

	this->setMapping(7,   tilset->getTile(3, 0), 0);
	this->setMapping(28,  tilset->getTile(3, 0), 90);
	this->setMapping(112, tilset->getTile(3, 0), 180);
	this->setMapping(193, tilset->getTile(3, 0), 270);

	this->setMapping(17, tilset->getTile(4, 0), 0);
	this->setMapping(68, tilset->getTile(4, 0), 180);

	this->setMapping(21, tilset->getTile(5, 0), 0);
	this->setMapping(84, tilset->getTile(5, 0), 90);
	this->setMapping(81, tilset->getTile(5, 0), 180);
	this->setMapping(69, tilset->getTile(5, 0), 270);

	this->setMapping(23,  tilset->getTile(6, 0), 0);
	this->setMapping(92,  tilset->getTile(6, 0), 90);
	this->setMapping(113, tilset->getTile(6, 0), 180);
	this->setMapping(197, tilset->getTile(6, 0), 270);

	this->setMapping(29,  tilset->getTile(7, 0), 0);
	this->setMapping(116, tilset->getTile(7, 0), 90);
	this->setMapping(209, tilset->getTile(7, 0), 180);
	this->setMapping(71,  tilset->getTile(7, 0), 270);

	this->setMapping(31,  tilset->getTile(8, 0), 0);
	this->setMapping(124, tilset->getTile(8, 0), 90);
	this->setMapping(241, tilset->getTile(8, 0), 180);
	this->setMapping(199, tilset->getTile(8, 0), 270);

	this->setMapping(85, tilset->getTile(9, 0), 0);

	this->setMapping(87,  tilset->getTile(10, 0), 0);
	this->setMapping(93,  tilset->getTile(10, 0), 90);
	this->setMapping(117, tilset->getTile(10, 0), 180);
	this->setMapping(213, tilset->getTile(10, 0), 270);
	
	this->setMapping(95,  tilset->getTile(11, 0), 0);
	this->setMapping(125, tilset->getTile(11, 0), 90);
	this->setMapping(245, tilset->getTile(11, 0), 180);
	this->setMapping(215, tilset->getTile(11, 0), 270);

	this->setMapping(119, tilset->getTile(12, 0), 0);
	this->setMapping(221, tilset->getTile(12, 0), 180);

	this->setMapping(127, tilset->getTile(13, 0), 0);
	this->setMapping(253, tilset->getTile(13, 0), 90);
	this->setMapping(247, tilset->getTile(13, 0), 180);
	this->setMapping(223, tilset->getTile(13, 0), 270);

	this->setMapping(255, tilset->getTile(14, 0), 0);

	std::stringstream messageMap;
	std::stringstream message;

	for (int j = 0; j < this->height; j++) {
		for (int i = 0; i < this->width; i++) {
		
			int cell = this->map[i][j];
			int value = cell == 1 ? this->toValue(i, j) : 0;

			message << " {" << std::to_string(value) << "}";
			messageMap << "[" << std::to_string(cell) << "]";

		}

		message << "\n";
		messageMap << "\n";

	}

	BOOST_LOG_TRIVIAL(info) << "\n" << messageMap.str();
	BOOST_LOG_TRIVIAL(info) << "\n" << message.str();
}

std::pair<Tile*, int> TileMap::getTileAt(int x, int y)
{

	std::pair<Tile*, int> result;

	if ( this->map[x][y] == 0 ) {
		return this->tilemapping[0];
	}

	return this->tilemapping[this->toValue(x, y)];

}

int TileMap::getWidth()
{
	return this->width;
}

int TileMap::getHeight()
{
	return this->height;
}

int TileMap::getCell(int x, int y)
{
	if (x < 0 || x > this->width - 1)  return 0;
	if (y < 0 || y > this->height - 1) return 0;
	return this->map[x][y];
}

int TileMap::toValue(int x, int y) {
	
	int value = 0;

	bool n  = this->getCell(x, y - 1) == 1;
	bool ne = this->getCell(x + 1, y - 1) == 1;
	bool e  = this->getCell(x + 1, y) == 1;
	bool se = this->getCell(x + 1, y + 1) == 1;
	bool s  = this->getCell(x, y + 1) == 1;
	bool sw = this->getCell(x - 1, y + 1) == 1;
	bool w  = this->getCell(x - 1, y) == 1;
	bool nw = this->getCell(x - 1, y - 1) == 1;

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

void TileMap::setMapping(int index, Tile* tile, int angle) {
	std::pair<Tile*, int> result;
	result.first = tile;
	result.second = angle;
	this->tilemapping[index] = result;
}
