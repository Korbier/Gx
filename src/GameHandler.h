#pragma once

#include <string>

#include <SDL.h>

#include "Display.h"
#include "display/texture/TextureManager.h"
#include "display/Sprite.h"
#include "display/texture/AnimatedTexture.h"
#include "display/texture/Texture.h"

class Game;

class GameHandler
{
public:

	GameHandler(Display* display, Game* game);

	/*Game control*/
	void stop();
	void render(Sprite* Sprite, SDL_Rect* target);
	void render(Texture* tile, int angle, SDL_Rect* target);

	/*Resource loader*/
	SDL_Texture* getTexture(std::string path);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

