#pragma once

#include <SDL.h>

class Display;
class GameHandler;

class Gamestate
{
public:
	
	void initialize(Display* display, GameHandler* gamehandler);
	void finalize();

	void input();
	void update();
	void render();

private:
	Display* display = nullptr;
	GameHandler* gameHandler = nullptr;

	SDL_Surface* image = nullptr;
	SDL_Texture* texture = nullptr;

};

