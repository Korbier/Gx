#include "GameHandler.h"

#include "Game.h"
#include "Display.h"
#include "TextureManager.h"
#include "Entity.h"
#include "AnimatedSprite.h"

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

void GameHandler::render(Entity* entity, SDL_Rect* target)
{
	SDL_RenderCopyEx(this->display->getRenderer(), entity->getSprite()->getTexture(), entity->getSprite()->getCrop(), target, entity->getAngle(), nullptr, SDL_FLIP_NONE);
}
