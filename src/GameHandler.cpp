#include "GameHandler.h"

#include "Game.h"
#include "Display.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "AnimatedTexture.h"
#include "Tile.h"

GameHandler::GameHandler(Display* display, Game* game)
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

void GameHandler::render(Sprite* Sprite, SDL_Rect* target)
{
	SDL_RenderCopyEx(this->display->getRenderer(), Sprite->getTexture()->getTexture(), Sprite->getTexture()->getCrop(), target, Sprite->getAngle(), nullptr, SDL_FLIP_NONE);
}

void GameHandler::render(Tile* tile, SDL_Rect* target)
{
	SDL_RenderCopy(this->display->getRenderer(), tile->getTexture()->getTexture(), tile->getTexture()->getCrop(), target);
}
