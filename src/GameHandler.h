#pragma once

#include <string>

#include <SDL.h>

#include "Display.h"
#include "display/texture/TextureManager.h"
#include "display/Sprite.h"
#include "display/texture/AnimatedTexture.h"
#include "display/texture/Texture.h"
#include "display/text/Text.h"

class Game;

class GameHandler
{
public:

	GameHandler(Display* display, Game* game);

	/*Game control*/
	void stop();
	void render(Sprite* Sprite, SDL_Rect* target);
	void render(Texture* tile, int angle, SDL_Rect* target);
	void render(Text* text, SDL_Rect* target);

	void render(SDL_Point start, SDL_Point end);

	void render(SDL_Rect rect);

	/*Resource loader*/
	SDL_Texture* getTexture(std::string path);

private:
	Display* display = nullptr;
	Game*    game    = nullptr;

};

