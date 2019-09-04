#include "GameHandler.h"

#include "Game.h"
#include "Display.h"
#include "TextureManager.h"
#include "Sprite.h"

void GameHandler::initialize(Display* display, Game* game)
{
	this->display = display;
	this->game    = game;
}

int GameHandler::getFramerate()
{
	return this->game->getFramerate();
}

void GameHandler::stop()
{
	this->game->stop();
}

SDL_Texture* GameHandler::getTexture(std::string path)
{
	return this->game->getTextureManager()->get(path);
}

void GameHandler::render(Sprite* sprite, SDL_Rect* target)
{
	SDL_RenderCopy(this->display->getRenderer(), sprite->getTexture(), sprite->getCrop(), target);
}
