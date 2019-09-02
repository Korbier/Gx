#pragma once

#include <string>
#include "SDL.h"

class Display;
class Game;
class TextureManager;
class Sprite;

class GameHandler
{
public:

	void initialize(Display* display, Game* game);

	void         stop();
	SDL_Texture* getTexture(std::string path);

	void render(Sprite* sprite);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

