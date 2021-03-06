#pragma once

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "boost/log/trivial.hpp"

#include "Display.h"
#include "GameHandler.h"
#include "display/texture/TextureManager.h"
#include "input/InputBuffer.h"
#include "gamestate/GameStateManager.h"
#include "gamestate/Gamestate.h"
#include "gamestate/MainMenuGamestate.h"
#include "utils/Timer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRAMES_PER_SECOND = 30;
const int TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

class Game
{
public:
	
	Game();
	~Game();

	void run();
	void stop();

	bool isRunning();

	TextureManager* getTextureManager();
	GameStateManager* getGameStateManager();

private:

	bool            running   = false;
	Display*        display   = nullptr;
	GameHandler*    gHandler  = nullptr;
	TextureManager* textureManager = nullptr;
	
	GameStateManager* gStateManager;
	InputBuffer      inputBuffer;

	
	void input();
	void render();

};
