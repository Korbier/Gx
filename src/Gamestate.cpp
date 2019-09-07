#include "Gamestate.h"

#include "boost/log/trivial.hpp"
#include "SDL_image.h"

#include "Display.h"
#include "GameHandler.h"
#include "AnimatedTexture.h"
#include "Sprite.h"
#include "InputBuffer.h"
#include "Tile.h"
#include "Tileset.h"
#include "TileMap.h"

const int TILE_SIZE = 32;

Gamestate::Gamestate(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;

	this->target = new SDL_Rect();
	this->target->w = this->target->h = TILE_SIZE;

	this->tileset = new Tileset();

	int height = 10;
	int width  = 10;

	int** map = new int* [width];

	for (int i = 0; i < width; i++) {

		map[i] = new int[height];

		for (int j = 0; j < height; j++) {
			map[i][j] = 0;
		}
	}

	map[1][1] = 1;
	map[2][1] = 1;
	map[2][2] = 1;
	map[1][2] = 1;
	map[1][3] = 1;
	map[3][2] = 1;
	map[2][3] = 1;
	map[3][3] = 1;

	this->tilemap = new TileMap(map, width, height);

}

Gamestate::~Gamestate()
{
	delete this->tank;
	delete this->target;
	delete this->tileset;
	delete this->tilemap;
}

void Gamestate::initialize() {
	
	this->tank = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(TANK_SPRITESHEET), 20), 0, 0);
	this->tank->setXVelocity( 300 );
	this->tank->setYVelocity( 300 );
	this->tank->getTexture()->addFrame( 0, 0, 32, 32);
	this->tank->getTexture()->addFrame(32, 0, 32, 32);
	this->tank->getTexture()->addFrame(64, 0, 32, 32);
	this->tank->getTexture()->addFrame(96, 0, 32, 32);

	this->tileset->loadTileset(this->gameHandler->getTexture(TILESET), 32);
	this->tilemap->load(this->tileset);
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

	for (int i = 0; i < this->tileset->getWidth(); i++) {
		for (int j = 0; j < this->tileset->getHeight(); j++) {
			this->target->x = i * 35;
			this->target->y = j * 35;
			this->gameHandler->render(this->tileset->getTile(i, j), target);
		}
	}
	
	this->target->x = (int)this->tank->getX();
	this->target->y = (int)this->tank->getY();
	this->gameHandler->render(this->tank, this->target);

}
