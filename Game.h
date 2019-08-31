#pragma once
#include "SDL.h"
#include "Window.h"
#include "Gamestate.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game
{
public:
	
	void initialize();
	void finalize();

	void run();
	void stop();

	bool isRunning();

private:

	bool       running = false;
	Window*    window  = NULL;
	Gamestate* state   = NULL; //TODO Mettre en place le gamestate manager

};

