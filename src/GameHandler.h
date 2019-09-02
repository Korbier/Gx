#pragma once

#include <string>
#include "SDL.h"

class Display;
class Game;
class TextureManager;

class GameHandler
{
public:

	void initialize(Display* display, Game* game);

	void         stop();
	SDL_Texture* getTexture(std::string path);

	void render(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

