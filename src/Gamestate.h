#pragma once

#include <SDL.h>
#include <string>

class Display;
class GameHandler;
class Entity;
class InputBuffer;

const float TANK_SPEED = 0;
const std::string TANK_SPRITESHEET = "resources/tank_move_002.png";

class Gamestate
{
public:
	
	Gamestate(Display* display, GameHandler* gamehandler);
	~Gamestate();

	void initialize();

	void update(InputBuffer* input, Uint32 delta);
	void render();

private:
	Display*     display     = nullptr;
	GameHandler* gameHandler = nullptr;

	Entity* tank = nullptr;
	SDL_Rect* crop = nullptr;

};