#include "Gamestate.h"

#include <vector>

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedTexture.h"
#include "Sprite.h"
#include "InputBuffer.h"
#include "Tile.h"
#include "Tileset.h"
#include "Map.h"
#include "MapTile.h"

const int TILE_SIZE = 32;

Gamestate::Gamestate(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;

	this->target = new SDL_Rect();
	this->target->w = this->target->h = TILE_SIZE;

	this->tileset = new Tileset();
	this->tileset2 = new Tileset();



	this->map = new Map();

}

Gamestate::~Gamestate()
{
	delete this->tank;
	delete this->target;
	delete this->tileset;
	delete this->tileset2;
}

void Gamestate::initialize() {

	int height = 20;
	int width = 25;

	this->tank = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(TANK_SPRITESHEET), 20), 0, 0);
	this->tank->setXVelocity( 300 );
	this->tank->setYVelocity( 300 );
	this->tank->getTexture()->addFrame( 0, 0, 32, 32);
	this->tank->getTexture()->addFrame(32, 0, 32, 32);
	this->tank->getTexture()->addFrame(64, 0, 32, 32);
	this->tank->getTexture()->addFrame(96, 0, 32, 32);

	this->tileset->loadTileset(this->gameHandler->getTexture(TILESET), 32);
	this->tileset2->loadTileset(this->gameHandler->getTexture(TILESET2), 32);

	this->map->addReference(0, this->tileset, 0, 0);
	this->map->addReference(1, this->tileset, true);
	this->map->addReference(2, this->tileset2, true);


	std::vector<std::vector<int>> m;

	for (int i = 0; i < width; i++) {
		std::vector<int> row;
		for (int j = 0; j < height; j++) {
			row.push_back(0);
		}
		m.push_back(row);
	}

	m[5][5] = 1;
	m[6][5] = 1;

	m[10][10] = 2;
	m[10][11] = 2;
	m[10][12] = 2;
	m[11][11] = 2;
	m[11][12] = 2;

	m[11][13] = 2;
	m[11][14] = 2;
	m[11][15] = 2;
	m[11][16] = 2;
	m[11][17] = 2;

	m[12][10] = 1;
	m[12][11] = 1;
	m[12][12] = 1;
	m[13][11] = 1;
	m[13][12] = 1;
	m[14][12] = 1;
	m[15][12] = 1;
	m[16][12] = 1;
	m[17][12] = 1;
	m[13][13] = 1;
	m[14][13] = 1;
	m[15][13] = 1;
	m[16][13] = 1;
	m[17][13] = 1;

	this->map->setData(m, width, height);

	this->map->debug();

}

void Gamestate::update(InputBuffer* input, Uint32 delta )
{
	
	float xVal = 0;
	float yVal = 0;

	if (input->isPressed(SDL_SCANCODE_RIGHT)) xVal = this->tank->getXVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_LEFT))  xVal = -1 * this->tank->getXVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_UP))    yVal = -1 * this->tank->getYVelocity() * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_DOWN))  yVal = this->tank->getYVelocity() * (delta / 1000.f);

	this->tank->move(xVal, yVal);
	
	bool animateTank = true;

	if (xVal > 0) {
		if (yVal > 0)      this->tank->setAngle(135.0);
		else if (yVal < 0) this->tank->setAngle(45.0);
		else               this->tank->setAngle(90.0);
	}
	else if (xVal < 0) {
		if (yVal > 0)      this->tank->setAngle(225.0);
		else if (yVal < 0) this->tank->setAngle(315.0);
		else               this->tank->setAngle(270.0);
	}
	else {
		if (yVal > 0)      this->tank->setAngle(180.0);
		else if (yVal < 0) this->tank->setAngle(0.0);
		else {
			animateTank = false;
		}
	}

	if (animateTank) {
		this->tank->getTexture()->animate();
	}

}

void Gamestate::render()
{

	
	for (int i = 0; i < this->map->getWidth(); i++) {
		for (int j = 0; j < this->map->getHeight(); j++) {
			this->target->x = i * 32;
			this->target->y = j * 32;

			MapTile* mTile = this->map->getTileAt(i, j);
			this->gameHandler->render(mTile->getTile(), mTile->getAngle(), target);

		}
	}

	this->target->x = (int)this->tank->getX();
	this->target->y = (int)this->tank->getY();
	this->gameHandler->render(this->tank, this->target);
	
}
