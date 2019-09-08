#include "TileMap.h"

#include "boost/log/trivial.hpp"
#include <sstream>
#include <string>

TileMap::TileMap(int** map, int width, int height)
{
	this->map = map;
	this->width  = width;
	this->height = height;
}

void TileMap::load(Tileset* tilset)
{

	std::stringstream messageMap;
	std::stringstream message;

	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {

			int cell = this->map[i][j];
			int value = cell == 1 ? this->toValue(j, i) : 0;

			message << " {" << std::to_string(value) << "}";
			messageMap << "[" << std::to_string(cell) << "]";

		}

		message << "\n";
		messageMap << "\n";

	}

	BOOST_LOG_TRIVIAL(info) << "\n" << messageMap.str();
	BOOST_LOG_TRIVIAL(info) << "\n" << message.str();
}

int TileMap::getCell(int x, int y)
{
	if (x < 0 || x > this->width - 1)  return 0;
	if (y < 0 || y > this->height - 1) return 0;
	return this->map[y][x];
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

