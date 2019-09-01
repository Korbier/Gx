#pragma once

#include <SDL.h>

class Window;
class GameHandler;

class Gamestate
{
public:
	
	void initialize(Window* window, GameHandler* gamehandler);
	void finalize();

	void input();
	void update();
	void render();

private:
	Window*      window      = nullptr;
	GameHandler* gameHandler = nullptr;

};

