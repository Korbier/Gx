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

	if (this->getCell(x, y - 1) == 1) {
		value += 1;  //North
	}
	/*
	if (this->getCell(x + 1, y - 1) == 1) {
		value += 2;  //North East
	}
	*/
	if (this->getCell(x + 1, y) == 1) {
		value += 4;  //East
	}
	/*
	if (this->getCell(x + 1, y + 1) == 1) {
		value += 8;  //South East
	}
	*/
	if (this->getCell(x, y + 1) == 1) {
		value += 16; //South
	}
	/*
	if (this->getCell(x - 1, y + 1) == 1) {
		value += 32; //South West
	}
	*/
	if (this->getCell(x - 1, y) == 1) {
		value += 64; //West
	}
	/*
	if (this->getCell(x - 1, y - 1) == 1) {
		value += 128;//North West
	}
	*/

	return value;

}

