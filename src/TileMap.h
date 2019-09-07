#pragma once

class Tileset;

class TileMap
{
public:
	TileMap(int** map, int width, int height );
	void load(Tileset* tilset);
private:

	int getCell(int x, int y);
	int toValue(int x, int j);

	int** map = {};
	int width;  //Nombre de cellules en largeur de la map
	int height; //Nombre de cellules en hauteur de la map
};

