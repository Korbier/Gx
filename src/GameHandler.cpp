#include "GameHandler.h"

#include "Game.h"
#include "Display.h"
#include "TextureManager.h"

void GameHandler::initialize(Display* display, Game* game)
{
	this->display = display;
	this->game    = game;
}

void GameHandler::stop()
{
	this->game->stop();
}

SDL_Texture* GameHandler::getTexture(std::string path)
{
	return this->game->getTextureManager()->get(path);
}

void GameHandler::render(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dst)
{
	SDL_RenderCopy(this->display->getRenderer(), texture, src, dst);
}
