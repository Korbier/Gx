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

void GameHandler::stop()
{
	this->game->stop();
}

SDL_Texture* GameHandler::getTexture(std::string path)
{
	return this->game->getTextureManager()->get(path);
}

void GameHandler::render(Sprite* sprite)
{
	SDL_RenderCopyEx(this->display->getRenderer(), sprite->getTexture(), sprite->getCrop(), sprite->getDstRect(), 90, NULL, SDL_FLIP_NONE);
}
