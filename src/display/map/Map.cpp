#include "Map.h"

void Map::addReference(int index, Tileset* tileset, bool solid, int tileX, int tileY)
{
	TileReference* reference = new TileReference(tileset, solid, tileX, tileY);
	this->references.insert(std::pair<int, TileReference*>(index, reference));
}

void Map::addReference(int index, Tileset* tileset, bool solid, bool merged)
{
	TileReference* reference = new TileReference(tileset, solid, merged);
	this->references.insert(std::pair<int, TileReference*>(index, reference));
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

void Map::setData(int x, int y, int value)
{
	this->data[x][y] = value;
	
	if (x > 0) {
		if ( y > 0 ) this->cache[x - 1][y - 1] = this->toMapTile(x - 1, y - 1, this->data[x - 1][y - 1]);
		this->cache[x - 1][y] = this->toMapTile(x - 1, y, this->data[x - 1][y]);
		if ( y < this->getHeight() - 1 ) this->cache[x - 1][y + 1] = this->toMapTile(x - 1, y + 1, this->data[x - 1][y + 1]);
	}

	if (y > 0) this->cache[x][y-1] = this->toMapTile(x, y-1, this->data[x][y - 1]);
	this->cache[x][y]   = this->toMapTile(x, y, this->data[x][y]);
	if (y < this->getHeight() - 1) this->cache[x][y+1] = this->toMapTile(x, y+1, this->data[x][y + 1]);

	if (x < this->getWidth() - 1) {
		if (y > 0) this->cache[x + 1][y - 1] = this->toMapTile(x + 1, y - 1, this->data[x + 1][y - 1]);
		this->cache[x + 1][y] = this->toMapTile(x + 1, y, this->data[x + 1][y]);
		if (y < this->getHeight() - 1) this->cache[x + 1][y + 1] = this->toMapTile(x + 1, y + 1, this->data[x + 1][y + 1]);
	}

}

void Map::toMapView(SDL_Point* point)
{
	point->x = point->x / 32;
	point->y = point->y / 32;
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
Tile* Map::getTileAt(int x, int y)
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

bool Map::collide(Sprite* sprite)
{

	int leftTile   = (int) sprite->getPosition().x / 32;
	int topTile    = (int) sprite->getPosition().y / 32;
	int rightTile  = (int) (sprite->getPosition().x + sprite->getSize().x - 1) / 32;
	int bottomTile = (int) (sprite->getPosition().y + sprite->getSize().y - 1) / 32;

	if (leftTile < 0) leftTile = 0;
	if (rightTile >= this->getWidth()) rightTile = this->getWidth() - 1;
	if (topTile < 0) topTile = 0;
	if (bottomTile >= this->getHeight()) bottomTile = this->getHeight() - 1;

	for (int i = leftTile; i <= rightTile; i++)
	{
		for (int j = topTile; j <= bottomTile; j++)
		{
			int cell = this->getData(i, j);
			if (this->references[cell]->isSolid()) {
				return true;
			}
		}
	}

	return false;

}

SDL_Point Map::getCellForRadialCollision(Sprite* sprite) {

	SDL_FPoint sCenter = sprite->getHitboxCenter();
	float      radius = sprite->getHitboxRadius();
	float      fullDistance = radius;

	SDL_FPoint mvt = radMvtToCoord(sprite->getAngle(), fullDistance);
	SDL_FPoint target = { sCenter.x + mvt.x, sCenter.y + mvt.y };

	int xTile = (int)target.x / 32;
	int yTile = (int)target.y / 32;

	return { xTile, yTile };

}

bool Map::checkBallCollision(SDL_Point cell) {
	
	int xTile = cell.x;
	int yTile = cell.y;

	if (xTile < 0) return true;
	if (xTile >= this->getWidth()) return true;
	if (yTile < 0) return true;
	if (yTile >= this->getHeight()) return true;

	int c = this->getData(xTile, yTile);
	return this->references[c]->isSolid();
	
}

float Map::checKCollisionX(Sprite* sprite, float decal)
{

	SDL_FPoint position = {
		sprite->getPosition().x + sprite->getHitbox().getPosition().x,
		sprite->getPosition().y + sprite->getHitbox().getPosition().y
	};

	SDL_Point size = { sprite->getHitbox().getSize().x, sprite->getHitbox().getSize().y };

	int topTile    = (int) position.y / 32;
	int bottomTile = (int) (position.y + size.y - 1) / 32;

	if (topTile < 0) topTile = 0;
	if (bottomTile >= this->getHeight()) bottomTile = this->getHeight() - 1;

	if (decal < 0) {
		
		int t = (int)(position.x + decal) / 32;
		if (t < 0) t = 0;

		for (int j = topTile; j <= bottomTile; j++) {
			int cell = this->getData(t, j);
			if (this->references[cell]->isSolid()) {
				return -1 * (position.x - (t + 1) * 32);
			}
		}
	}

	if (decal > 0) {
		
		int t = (int)(position.x + decal + size.x) / 32;
		if (t >= this->getWidth()) t = this->getWidth() - 1;

		for (int j = topTile; j <= bottomTile; j++) {
			int cell = this->getData(t, j);
			if (this->references[cell]->isSolid()) {
				float d = t * 32 - (position.x + size.x);
				return d;
			}
		}
	}

	return decal;
}

float Map::checKCollisionY(Sprite* sprite, float decal)
{

	SDL_FPoint position = {
		sprite->getPosition().x + sprite->getHitbox().getPosition().x,
		sprite->getPosition().y + sprite->getHitbox().getPosition().y
	};

	SDL_Point size = { sprite->getHitbox().getSize().x, sprite->getHitbox().getSize().y };

	int leftTile = (int)position.x / 32;
	int rightTile = (int)(position.x + size.x - 1) / 32;

	if (leftTile < 0) leftTile = 0;
	if (rightTile >= this->getWidth()) rightTile = this->getWidth() - 1;

	if (decal < 0) {

		int t = (int)(position.y + decal) / 32;
		if (t < 0) t = 0;

		for (int j = leftTile; j <= rightTile; j++) {
			int cell = this->getData(j, t);
			if (this->references[cell]->isSolid()) {
				return -1 * (position.y - (t + 1) * 32);
			}
		}
	}

	if (decal > 0) {

		int t = (int)(position.y + decal + size.y) / 32;
		if (t >= this->getHeight()) t = this->getHeight() - 1;

		for (int j = leftTile; j <= rightTile; j++) {
			int cell = this->getData(j, t);
			if (this->references[cell]->isSolid()) {
				float d = t * 32 - (position.y + size.y);
				return d;
			}
		}
	}

	return decal;

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

Tile* Map::toMapTile(int x, int y, int data) {

	TileReference* reference = this->references[data];
	Texture* tile = nullptr;
	int angle = 0;

	if (reference->isAutoTile()) {

		int autoIndex = this->toAutoTileIndex(data, reference, x, y);

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

	return new Tile(tile, angle, reference);

}

void Map::loadCache()
{

	for (int i = 0; i < this->getWidth(); i++) {
		std::vector<Tile*> row;
		for (int j = 0; j < this->getHeight(); j++) {
			int data = this->getData(i, j);
			row.push_back( this->toMapTile(i, j, data) );
		}
		this->cache.push_back(row);
	}
}

bool Map::isNeighbour(int data, TileReference* reference, int x, int y) {

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

int Map::toAutoTileIndex(int data, TileReference* reference, int x, int y) {

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



