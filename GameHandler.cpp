#include "GameHandler.h"

#include "Game.h"

void GameHandler::initialize(Game* game)
{
	this->game = game;
}

void GameHandler::stop()
{
	this->game->stop();
}
