#include "GameHandler.h"

#include "Game.h"

GameHandler::GameHandler(Display* display, Game* game)
{
	this->display = display;
	this->game    = game;
}

void GameHandler::stop()
{
	this->game->stop();
}

void GameHandler::push(Gamestate* gstate)
{
	this->game->getGameStateManager()->push(gstate);
}

void GameHandler::pop()
{
	this->game->getGameStateManager()->pop();
}

void GameHandler::pop( unsigned int count )
{
	this->game->getGameStateManager()->pop(count);
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
	//SDL_SetRenderDrawColor(this->display->getRenderer(), 250, 250, 250, 255);
	//SDL_RenderDrawRect(this->display->getRenderer(), target);
}

void GameHandler::render(Text* text, SDL_Rect* target)
{
	SDL_Rect src = { 0, 0, text->getWith(), text->getHeight() };
	SDL_Rect tgt = { target->x, target->y, text->getWith(), text->getHeight() };
	SDL_RenderCopyEx(this->display->getRenderer(), text->getTexture(), &src, &tgt, text->getAngle(), nullptr, SDL_FLIP_NONE);
}

void GameHandler::render(SDL_Point start, SDL_Point end) 
{
	SDL_SetRenderDrawColor(this->display->getRenderer(), 250, 0, 0, 255);
	SDL_RenderDrawLine(this->display->getRenderer(), start.x, start.y, end.x, end.y);
}

void GameHandler::render(SDL_Rect rect, bool fill, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(this->display->getRenderer(), r, g, b, a);
	if (fill) {
		SDL_RenderFillRect(this->display->getRenderer(), &rect);
	}
	else {
		SDL_RenderDrawRect(this->display->getRenderer(), &rect);
	}
}
