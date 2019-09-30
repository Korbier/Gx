#pragma once

#include <string>
#include <vector>
#include <cstdlib>

#include <SDL.h>
#include <SDL_image.h>

#include "boost/log/trivial.hpp"

#include "Game.h"
#include "Display.h"
#include "GameHandler.h"
#include "display/texture/AnimatedTexture.h"
#include "display/Sprite.h"
#include "input/InputBuffer.h"
#include "display/Tileset.h"
#include "display/map/Map.h"
#include "display/map/Tile.h"
#include "display/Camera.h"

#include "game/bullet/Bullet.h"
#include "game/bullet/BulletDescriptor.h"
#include "game/bullet/BulletGenerator.h"

const int TILE_SIZE = 32;

const float TANK_SPEED = 0;
const std::string TANK_SPRITESHEET = "resources/tank_move_002.png";
const std::string BULLET_SPRITESHEET = "resources/sprite_bullet.png";
const std::string TILESET_OLD = "resources/wang-blob-tilesets.png";
const std::string TILESET = "resources/tileset_01.png";
const std::string TILESET2 = "resources/tileset_02.png";

class Gamestate
{
public:
	
	Gamestate(Display* display, GameHandler* gamehandler);
	~Gamestate();

	void initialize();

	void update(InputBuffer input, Uint32 delta);
	void render();

private:
	Display*     display     = nullptr;
	GameHandler* gameHandler = nullptr;

	Sprite* tank   = nullptr;
	
	SDL_Rect* target = nullptr;

	Tileset* tileset = nullptr;
	Tileset* tileset2 = nullptr;
	
	Map* map = nullptr;

	Camera* camera;

	BulletDescriptor* bDesc = nullptr;
	BulletGenerator* bGen = nullptr;

};