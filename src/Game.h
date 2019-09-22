#pragma once

#include "SDL.h"
#include "input/InputBuffer.h"
#include "gamestate/GameStateManager.h"

const int SCREEN_WIDTH      = 800;
const int SCREEN_HEIGHT     = 600;
const int FRAMES_PER_SECOND = 30;
const int TICKS_PER_FRAME   = 1000 / FRAMES_PER_SECOND;

class GameHandler;
class Display;
class GameStateManager;
class Gamestate;
class Timer;
class TextureManager;

class Game
{
public:
	
	Game();
	~Game();

	void run();
	void stop();

	bool isRunning();

	TextureManager* getTextureManager();

private:

	bool            running   = false;
	Display*        display   = nullptr;
	GameHandler*    gHandler  = nullptr;
	TextureManager* textureManager = nullptr;
	
	GameStateManager gStateManager;
	InputBuffer      inputBuffer;

	
	void input();
	void render();

};
