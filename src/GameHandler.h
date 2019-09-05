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

	GameHandler(Display* display, Game* game);

	/*Game control*/
	void stop();
	void render(Sprite* sprite, SDL_Rect* target);

	/*Resource loader*/
	SDL_Texture* getTexture(std::string path);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

