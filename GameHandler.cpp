#include "GameHandler.h"

#include "Game.h"
#include "TextureManager.h"

void GameHandler::initialize(Game* game)
{
	this->game = game;
}

void GameHandler::stop()
{
	this->game->stop();
}

SDL_Texture* GameHandler::getTexture(std::string path)
{
	return this->game->getTextureManager()->get(path);
}
