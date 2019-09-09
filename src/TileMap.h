#pragma once

#include <vector>
#include <utility>

class Tileset;
class Tile;

class TileMap
{
public:
	TileMap(std::vector<std::vector<int>> map, int width, int height );
	
	void load(Tileset* tilset);

	std::pair<Tile*, int> getTileAt(int x, int y);
	int getWidth();
	int getHeight();

private:

	int getCell(int x, int y);
	int toValue(int x, int j);

	std::vector<std::vector<int>> map;
	int width;  //Nombre de cellules en largeur de la map
	int height; //Nombre de cellules en hauteur de la map

	std::pair<Tile*, int> tilemapping[255];
	void setMapping(int index, Tile* tile, int angle);

};

