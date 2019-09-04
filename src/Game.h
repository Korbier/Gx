#pragma once

#include "SDL.h"

const int SCREEN_WIDTH      = 800;
const int SCREEN_HEIGHT     = 600;
const int FRAMES_PER_SECOND = 120;
const int TICKS_PER_FRAME   = 1000 / FRAMES_PER_SECOND;

class GameHandler;
class Display;
class Gamestate;
class Timer;
class TextureManager;

class Game
{
public:
	
	void initialize();
	void finalize();

	void run();
	void stop();

	bool isRunning();
	int  getFramerate();

	TextureManager* getTextureManager();

private:

	bool         running   = false;
	Display*     display   = nullptr;
	Gamestate*   state     = nullptr; //TODO Mettre en place le gamestate manager
	GameHandler* gHandler  = nullptr;
	TextureManager* textureManager = nullptr;
	
	/* Framerate */
	Uint32 next_time = 0;
	Uint32 time_left();

	void input();
	void render();

};

