#pragma once

#include <SDL.h>

class Display;
class GameHandler;

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
	SDL_Texture* texture     = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Rect* src = nullptr;
	SDL_Rect* dst = nullptr;

};

