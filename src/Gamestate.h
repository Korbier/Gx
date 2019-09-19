#pragma once

#include <SDL.h>
#include <string>

class Display;
class GameHandler;
class Sprite;
class InputBuffer;
class Tile;
class Tileset;
class TileMap;
class Map;
class Camera;
class Bullet;

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
	Bullet* bullet = nullptr;
	
	SDL_Rect* target = nullptr;

	Tileset* tileset = nullptr;
	Tileset* tileset2 = nullptr;
	
	Map* map = nullptr;

	Camera* camera;

};