#pragma once
#include "SDL.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

class GameHandler;
class Window;
class Gamestate;

class Game
{
public:
	
	void initialize();
	void finalize();

	void run();
	void stop();

	bool isRunning();

private:

	bool         running  = false;
	Window*      window   = nullptr;
	Gamestate*   state    = nullptr; //TODO Mettre en place le gamestate manager
	GameHandler* gHandler = nullptr;

	void render();

};

