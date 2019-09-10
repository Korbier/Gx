#pragma once

#include <map>
#include <vector>
#include <utility>

class MapTileReference;
class Tileset;
class Tile;

class Map {
public:
	
	Map();

	void addReference(int index, Tileset* tileset, int tileX, int tileY);
	void addReference(int index, Tileset* tileset, bool merged);

	void setData(std::vector<std::vector<int>> data);

	Tile* getTileAt(int x, int y);

private:
	std::map<int, MapTileReference*> references;
	std::vector<std::vector<int>> data;
	
	//Autotiling
	std::map<int, int> rotations;
	std::map<int, std::pair<int, int>> indexes;
	void loadRotations();
	void loadIndexes();
	Tile* getAutoTile(MapTileReference* reference);

};