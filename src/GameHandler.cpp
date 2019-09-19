#include "GameHandler.h"

#include "Game.h"
#include "Display.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "AnimatedTexture.h"
#include "Texture.h"

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

void GameHandler::render(Sprite* sprite, SDL_Rect* target)
{
	SDL_RenderCopyEx(this->display->getRenderer(), sprite->getTexture()->getTexture(), &(sprite->getTexture()->getCrop()), target, sprite->getAngle(), nullptr, SDL_FLIP_NONE);
}

void GameHandler::render(Texture* texture, int angle, SDL_Rect* target)
{
	SDL_RenderCopyEx(this->display->getRenderer(), texture->getTexture(), &(texture->getCrop()), target, angle, nullptr, SDL_FLIP_NONE);
}
