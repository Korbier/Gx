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

	/* Game configuration */
	int getFramerate();

	/*Game control*/
	void stop();
	void render(Sprite* sprite, SDL_Rect* target);

	/*Resource loader*/
	SDL_Texture* getTexture(std::string path);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

