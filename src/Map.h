#pragma once

#include <map>
#include <vector>
#include <utility>

class MapTileReference;
class Tileset;
class Tile;
class MapTile;

class Map {
public:
	
	Map();

	void addReference(int index, Tileset* tileset, int tileX, int tileY);
	void addReference(int index, Tileset* tileset, bool merged);

	void setData(std::vector<std::vector<int>> data, int width, int height);

	MapTile* getTileAt(int x, int y);

	int getWidth();
	int getHeight();

	void debug();

private:
	std::map<int, MapTileReference*> references;
	std::vector<std::vector<int>> data;
	std::vector<std::vector<MapTile*>> cache;
	int width = 0;
	int height = 0;
	
	//Autotiling
	std::map<int, int> rotations;
	std::map<int, std::pair<int, int>> indexes;
	
	void loadRotations();
	void loadIndexes();
	void loadCache();

	bool isNeighbour(int data, MapTileReference* reference, int x, int y);

	int toAutoTileIndex(int data, MapTileReference* reference, int x, int y);
	int getData(int x, int y);

};