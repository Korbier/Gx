#pragma once

#include <SDL.h>
#include <string>

class Display;
class GameHandler;
class AnimatedSprite;

const Uint32 TANK_SPEED = 0;
const std::string TANK_SPRITESHEET = "resources/tank_move_002.png";

class Gamestate
{
public:
	
	void initialize(Display* display, GameHandler* gamehandler);
	void finalize();

	void input(SDL_Event* event);
	void update();
	void render();

private:
	Display*     display     = nullptr;
	GameHandler* gameHandler = nullptr;

	AnimatedSprite* tank = nullptr;
	SDL_Rect* crop = nullptr;

};

