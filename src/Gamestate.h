#pragma once

#include <SDL.h>

class Display;
class GameHandler;
class AnimatedSprite;

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

