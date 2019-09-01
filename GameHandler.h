#pragma once

#include <string>
#include "SDL.h"

class Game;
class TextureManager;

class GameHandler
{
public:

	void initialize(Game* game);

	void         stop();
	SDL_Texture* getTexture(std::string path);

private:
	Game*     game = nullptr;

};

