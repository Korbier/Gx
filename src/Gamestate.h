#pragma once

#include <SDL.h>
#include <string>

class Display;
class GameHandler;
class Sprite;
class InputBuffer;

const float TANK_SPEED = 0;
const std::string TANK_TextureSHEET = "resources/tank_move_002.png";

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

	Sprite* tank = nullptr;
	SDL_Rect* crop = nullptr;

};