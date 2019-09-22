#pragma once

#include <map>
#include <vector>
#include <utility>

#include "SDL.h"

class MapTileReference;
class Tileset;
class Tile;
class MapTile;
class Sprite;

class Map {
public:
	
	Map();

	void addReference(int index, Tileset* tileset, bool solid, int tileX, int tileY);
	void addReference(int index, Tileset* tileset, bool solid, bool merged);

	MapTile* toMapTile(int x, int y, int data);
	void setData(std::vector<std::vector<int>> data, int width, int height);
	void setData(int x, int y, int value);

	MapTile* getTileAt(int x, int y);
	void boundToMap(Sprite* sprite);
	bool collide(Sprite* sprite);

	int getWidth();
	int getHeight();

	void toMapView(SDL_Point* point);
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